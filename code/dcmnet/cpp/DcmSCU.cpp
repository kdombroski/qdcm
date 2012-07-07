#include <QDebug>
#include <QTimer>
#include "DcmCEchoRequest.h"
#include "DcmSCU.h"

DcmSCU::DcmSCU(QObject *parent)
    : QObject(parent),
      m_state(DcmSCU::State_NotConnected),
      m_id(0)
{
    m_communicatorPtr = new DcmCommunicator();
    QTcpSocket *sock = m_communicatorPtr->socket();

    connect(sock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    connect(sock, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(onSocketStateChange(QAbstractSocket::SocketState)));
    connect(sock, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
    connect(sock, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));

    m_dimseTimerPtr = new QTimer();
    connect(m_dimseTimerPtr, SIGNAL(timeout()), this, SLOT(onDimseTimeout()));
}

DcmSCU::~DcmSCU()
{
    delete m_dimseTimerPtr;
    delete m_communicatorPtr;
}

DcmSCU::State DcmSCU::state() const
{
    return m_state;
}

void DcmSCU::setState(DcmSCU::State s)
{
    if (m_state != s) {
        m_state = s;
        emit stateChanged();
    }
}

void DcmSCU::connectToSCP(const QString &hostName, int port)
{
    if (state() != DcmSCU::State_NotConnected) {
        qWarning() << "Cannot connect to" << hostName << ":" << port
                   << "- SCU is already connected";
        return;
    }

    m_communicatorPtr->connectToHost(hostName, port);
    QTimer::singleShot(m_communicatorPtr->timeout(), this, SLOT(onConnectionTimeout()));
}

void DcmSCU::close()
{
    m_communicatorPtr->close();
    setState(DcmSCU::State_NotConnected);
}

void DcmSCU::sendAssociationRequest(const DcmAAssociateRequest &request)
{
    if (state() != DcmSCU::State_Connected) {
        qWarning() << "SCU state is invalid. Cannot send association request";
        return;
    }

    m_communicatorPtr->sendPDUItem(request);
    if (m_communicatorPtr->status() == DcmCommunicator::Status_Ok) {
        m_associateRequest = request;
        setState(DcmSCU::State_AssociationRequest);
        QTimer::singleShot(m_communicatorPtr->timeout(), this, SLOT(onAssociationTimeout()));
    } else {
        qWarning() << "SCU failed to send association request. Connection will be closed.";
        close();
    }

}

void DcmSCU::sendDimseCommand(DcmDimseMessage &message, int contextId)
{
    if (!transferSyntaxForAcceptedContextId(contextId).isValid()) {
        qWarning() << "DICOM SCU: context" << contextId << "has not been negociated.";
        return;
    }

    message.setMessageId(getNextMessageId());
    m_communicatorPtr->sendDimseMessage(message, contextId);
    if (m_communicatorPtr->status() == DcmCommunicator::Status_Ok) {
        setState(DcmSCU::State_DimseCommand);
        // Launch timer to detect DIMSE response timeout
        m_dimseTimerPtr->setInterval(m_communicatorPtr->timeout());
        m_dimseTimerPtr->setSingleShot(true);
    } else {
        qWarning() << "DICOM SCU failed to send DIMSE command. Connection will be closed.";
        close();
        emit dimseError();
    }
}

void DcmSCU::sendDimseDataset(DcmDataset &dataset, int contextId)
{
    DcmTransferSyntax syntax = transferSyntaxForAcceptedContextId(contextId);
    if (syntax.isValid()) {
        m_communicatorPtr->sendDataset(dataset, contextId, false, syntax);
    } else {
        qWarning() << "DICOM SCU failed to send data for presentation context"
                   << contextId << "since it has not been negociated.";
        close();
        emit dimseError();
    }
}

void DcmSCU::sendCEcho()
{
    DcmCEchoRequest cEchoRequest;

    int id = -1; // Presentation context id

    // Getting verification context id
    for (int i = 0; i < m_associateRequest.numberOfPresentationContexts(); i++) {
        DcmPresentationContext *pc = m_associateRequest.presentationContextAt(i);

        if (pc->abstractSyntax() == DcmAbstractSyntax::Verification) {
            id = pc->id();
        }
    }

    if (id < 0) {
        qWarning() << "Verification (C-ECHO) presentation context has not been proposed by association.";
        emit dimseError();
        return;
    }

    int aid = -1;

    // Check if the context has been accepted
    for (int i = 0; i < m_associateAccept.numberOfAcceptedPresentationContexts(); i++) {
        DcmAcceptedPresentationContext *apc = m_associateAccept.acceptedPresentationContextAt(i);
        if (apc->id() == id) {
            if (!apc->transferSyntax().isValid()) {
                qWarning() << "Accepted verification context has invalid transfer syntax";
                emit dimseError();
                return;
            }
            aid = id;
            break;
        }
    }

    if (aid < 0) {
        qWarning() << "Verification context has not been accepted by SCP.";
        emit dimseError();
        return;
    }

    sendDimseCommand(cEchoRequest, id);
}

DcmAAssociateRequest DcmSCU::associationRequest() const
{
    return m_associateRequest;
}

DcmAAssociateAccept DcmSCU::associationAccept() const
{
    return m_associateAccept;
}

DcmAAssociateReject DcmSCU::associationReject() const
{
    return m_associateReject;
}

const DcmDimseRequest& DcmSCU::dimseRequest() const
{
    return m_dimseRequest;
}

const DcmDimseResponse& DcmSCU::dimseResponse() const
{
    return m_dimseResponse;
}


int DcmSCU::getNextMessageId()
{
    return ++m_id;
}

int DcmSCU::messageId() const
{
    return m_id;
}

void DcmSCU::onSocketStateChange(QAbstractSocket::SocketState s)
{
    if (s == QAbstractSocket::ConnectedState) {
        // Reset messages counter
        m_id = 0;
        setState(DcmSCU::State_Connected);
    }
}

void DcmSCU::onSocketError(QAbstractSocket::SocketError error)
{
    emit socketError();
}

void DcmSCU::onSocketDisconnected()
{
    setState(DcmSCU::State_NotConnected);
}

void DcmSCU::onConnectionTimeout()
{
    if (state() == DcmSCU::State_NotConnected) {
        emit connectionTimeout();
    }
}

void DcmSCU::onAssociationTimeout()
{
    if (state() == DcmSCU::State_AssociationRequest) {
        // Any other state means that association request phase is passed
        emit associationTimeout();
    }
}

void DcmSCU::onDimseTimeout()
{
    emit dimseTimeout();
}

void DcmSCU::onDataAvailable()
{

}

DcmTransferSyntax DcmSCU::transferSyntaxForAcceptedContextId(int contextId)
{
    for (int i = 0; i < m_associateAccept.numberOfAcceptedPresentationContexts(); i++) {
        DcmAcceptedPresentationContext *contextPtr = m_associateAccept.acceptedPresentationContextAt(i);
        Q_ASSERT(contextPtr);
        if (contextPtr->id() == contextId) {
            return contextPtr->transferSyntax();
        }
    }
    return DcmTransferSyntax::Invalid;
}

void DcmSCU::handleAssociationAccept(const DcmAAssociateAccept &ac)
{
    m_associateAccept = ac;
    DcmPDUUserInfo userInfo = ac.userInfoPDU();
    DcmSize pduSize = userInfo.pduMaxLength();
    m_communicatorPtr->setPduMaxLength(pduSize);

    setState(DcmSCU::State_AssociationAccept);
    emit associationAccepted();
}

void DcmSCU::handleAssociationReject(const DcmAAssociateReject &rj)
{
    m_associateReject = rj;
    emit associationRejected();
    close();
}

void DcmSCU::handleDimseRawMessage(bool command)
{

}
