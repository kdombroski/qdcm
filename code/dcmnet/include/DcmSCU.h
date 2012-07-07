#ifndef DCMSCU_H
#define DCMSCU_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include "DcmNetApi.h"
#include "DcmCommunicator.h"
#include "DcmAAssociateRequest.h"
#include "DcmAAssociateAccept.h"
#include "DcmAAssociateReject.h"
#include "DcmDimseMessage.h"
#include "DcmDimseRequest.h"
#include "DcmDimseResponse.h"
#include "DcmDataset.h"

class DCM_NET_API DcmSCU: public QObject
{
    Q_OBJECT

public:

    /**
     * SCU internal state.
     */
    typedef enum {
        State_NotConnected,         ///< SCU is not connected to any SCP.
        State_Connected,            ///< SCU is connected to SCP, but not associated.
        State_AssociationRequest,   ///< Association request sent.
        State_AssociationAccept,    ///< Association accepted.
        State_DimseCommand,         ///< Waiting for DIMSE command.
        State_DimseData,            ///< Waiting for DIMSE data.
        State_AssociationRelease    ///< Releasing association.
    } State;

    DcmSCU(QObject *parent = 0);
    ~DcmSCU();

    DcmSCU::State state() const;

    void connectToSCP(const QString &hostName, int port);
    void close();

    void sendAssociationRequest(const DcmAAssociateRequest &request);

    /**
     * The message will be updated with an id.
     */
    void sendDimseCommand(DcmDimseMessage &message, int contextId);
    void sendDimseDataset(DcmDataset &dataset, int contextId);

    void sendCEcho();
    void abortAssociation();
    void releaseAssociation();

    int timeout() const;
    void setTimeout(int t);

    DcmAAssociateRequest associationRequest() const;
    DcmAAssociateAccept associationAccept() const;
    DcmAAssociateReject associationReject() const;

    const DcmDimseRequest& dimseRequest() const;
    const DcmDimseResponse& dimseResponse() const;

signals:

    void connectionTimeout();
    void socketError();
    void associationTimeout();
    void dimseTimeout();
    void dimseError();
    void stateChanged();
    void associationAccepted();
    void associationRejected();
    void dimseCommandResponse();
    void dimseDataset(const DcmDataset &dataset);

private slots:

    void onDataAvailable();
    void onSocketStateChange(QAbstractSocket::SocketState s);
    void onSocketError(QAbstractSocket::SocketError error);
    void onSocketDisconnected();
    void onConnectionTimeout();
    void onAssociationTimeout();
    void onDimseTimeout();

private:

    Q_DISABLE_COPY(DcmSCU)

    void setState(DcmSCU::State s);
    int getNextMessageId();
    int messageId() const;

    /**
     * Returns negociated transfer syntax for specified context ID.
     * If no context ID is found, Invalid transfer syntax is returned.
     * \param contextId Context ID.
     * \return Negociated transfer syntax.
     */
    DcmTransferSyntax transferSyntaxForAcceptedContextId(int contextId);

    void handleAssociationAccept(const DcmAAssociateAccept &ac);
    void handleAssociationReject(const DcmAAssociateReject &rj);
    void handleDimseRawMessage(bool command);

    DcmSCU::State m_state;  ///< SCU state.

    DcmCommunicator *m_communicatorPtr; ///< Communicator object.

    int m_id;   ///< DIMSE message id.

    DcmAAssociateRequest m_associateRequest;
    DcmAAssociateAccept m_associateAccept;
    DcmAAssociateReject m_associateReject;

    DcmDimseRequest m_dimseRequest;
    DcmDimseResponse m_dimseResponse;

    QTimer *m_dimseTimerPtr;
};

#endif // DCMSCU_H
