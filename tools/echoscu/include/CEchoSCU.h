#ifndef CECHOSCU_H
#define CECHOSCU_H

#include <QObject>
#include "DcmSCU.h"

class CEchoSCU: public QObject
{
    Q_OBJECT

public:

    CEchoSCU(QObject *parent = 0);
    ~CEchoSCU();

    void setHost(const QString &host);
    void setPort(int port);
    void setCallingAE(const QString &ae);
    void setCalledAE(const QString &ae);

public slots:

    /// Perform C-Echo transaction
    void perform();

signals:

    void over();

private slots:

    void onScuStateChange();
    void onAssociationAccepted();
    void onAssociationRejected();
    void onAssociationTimeout();
    void onDimseResponse();
    void onSocketError();
    void onConnectionTimeout();
    void onDimseResposeTimeout();
    void onDimseError();

private:

    void requestAssociation();
    void releaseAssociation();

    DcmSCU *m_scuPtr;
    QString m_host;
    int m_port;
    QString m_callingAE;
    QString m_calledAE;
};

#endif // CECHOSCU_H
