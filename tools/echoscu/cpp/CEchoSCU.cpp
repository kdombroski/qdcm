#include <QDebug>
#include "CEchoSCU.h"

CEchoSCU::CEchoSCU(QObject *parent)
    : QObject(parent)
{
    m_scuPtr = new DcmSCU();
    m_host = "";
    m_port = 104;
    m_callingAE = "QDCM-SCU";
    m_calledAE = "ANYSCP";

    connect(m_scuPtr, SIGNAL(associationAccepted()), this, SLOT(onAssociationAccepted()));
    connect(m_scuPtr, SIGNAL(associationRejected()), this, SLOT(onAssociationRejected()));
    connect(m_scuPtr, SIGNAL(associationTimeout()), this, SLOT(onAssociationTimeout()));
    connect(m_scuPtr, SIGNAL(stateChanged()), this, SLOT(onScuStateChange()));
    connect(m_scuPtr, SIGNAL(dimseCommandResponse()), this, SLOT(onDimseResponse()));
    connect(m_scuPtr, SIGNAL(connectionTimeout()), this, SLOT(onConnectionTimeout()));
    connect(m_scuPtr, SIGNAL(dimseTimeout()), this, SLOT(onDimseResposeTimeout()));
    connect(m_scuPtr, SIGNAL(dimseError()), this, SLOT(onDimseError()));
}

CEchoSCU::~CEchoSCU()
{
    delete m_scuPtr;
}

void CEchoSCU::setHost(const QString &host)
{
    m_host = host;
}

void CEchoSCU::setPort(int port)
{
    m_port = port;
}

void CEchoSCU::setCallingAE(const QString &ae)
{
    m_callingAE = ae;
}

void CEchoSCU::setCalledAE(const QString &ae)
{
    m_calledAE = ae;
}

void CEchoSCU::perform()
{
    m_scuPtr->connectToSCP(m_host, m_port);
}

void CEchoSCU::onScuStateChange()
{
    qDebug() << __FUNCTION__;
    DcmSCU::State state = m_scuPtr->state();
    if (state == DcmSCU::State_Connected) {
        requestAssociation();
    }
}

void CEchoSCU::onAssociationAccepted()
{
    qDebug() << __FUNCTION__;
    if (m_scuPtr->associationAccept().numberOfAcceptedPresentationContexts() < 1) {
        qDebug() << "Presentation context has not been accepted by SCU.";
        releaseAssociation();
        return;
    }

    m_scuPtr->sendCEcho();
}

void CEchoSCU::onAssociationRejected()
{
    qDebug() << __FUNCTION__;
    qDebug() << m_scuPtr->associationReject().reasonAsString();

    m_scuPtr->close();
}

void CEchoSCU::onAssociationTimeout()
{
    qDebug() << __FUNCTION__;
    m_scuPtr->close();
}

void CEchoSCU::onDimseResponse()
{
    qDebug() << __FUNCTION__;
    if (m_scuPtr->dimseResponse().command() != DcmCommandType_CEchoResponse) {
        qDebug() << "Invalid DIMSE response received.";
    } else {
        DcmDimseResponse::Status status = m_scuPtr->dimseResponse().status();
        if (status == DcmDimseResponse::Status_Success) {
            qDebug() << "C-ECHO OK";
        } else {
            qDebug() << "C-ECHO error status:" << status;
        }
    }

    releaseAssociation();
}

void CEchoSCU::onConnectionTimeout()
{
    qDebug() << __FUNCTION__;
    m_scuPtr->close();
}

void CEchoSCU::onDimseResposeTimeout()
{
    qDebug() << __FUNCTION__;
    releaseAssociation();
}

void CEchoSCU::onDimseError()
{
    qDebug() << __FUNCTION__;
    releaseAssociation();
}

void CEchoSCU::requestAssociation()
{

}

void CEchoSCU::releaseAssociation()
{

}
