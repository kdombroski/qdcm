#ifndef DCMAASSOCIATEACCEPT_H
#define DCMAASSOCIATEACCEPT_H

#include <QString>
#include "DcmPDUItem.h"
#include "DcmApplicationContext.h"
#include "DcmAcceptedPresentationContext.h"
#include "DcmPDUUserInfo.h"
#include "DcmPDUItemList.h"
#include "DcmStream.h"
#include "DcmNetApi.h"

/*! DICOM association acceptance PDU.
 * This class handles DICOM association acceptance.
 * It contains a list of accepted abstract syntaxes
 * along with chosen transfer syntaxes to be used in
 * DIMSE transactions.
 */
class DCM_NET_API DcmAAssociateAccept: public DcmPDUItem
{
public:

    DcmAAssociateAccept();
    DcmAAssociateAccept(const DcmAAssociateAccept &pdu);
    DcmAAssociateAccept& operator =(const DcmAAssociateAccept &pdu);
    DcmPDUItem* clone() const;
    ~DcmAAssociateAccept();
    DcmUnsignedShort protocolVersion() const;
    void setProtocolVersion(DcmUnsignedShort version);
    QString calledAE() const;
    void setCalledAE(const QString &ae);
    QString callingAE() const;
    void setCallingAE(const QString &ae);
    DcmApplicationContext applicationContext() const;
    void setApplicationContext(const DcmApplicationContext &ac);
    int numberOfAcceptedPresentationContexts() const;
    DcmAcceptedPresentationContext* acceptedPresentationContextAt(int index) const;
    void addAcceptedPresentationContext(const DcmAcceptedPresentationContext &apc);
    void addAndRetainAcceptedPresentationContext(DcmAcceptedPresentationContext *apcPtr);
    DcmPDUUserInfo userInfoPDU() const;
    void setUserInfoPDU(const DcmPDUUserInfo &pdu);
    DcmSize size() const;
    DcmSize contentSize() const;
    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmAAssociateAccept &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmAAssociateAccept &pdu);

private:

    DcmUnsignedShort m_protocolVersion;
    QString m_calledAE;
    QString m_callingAE;
    DcmApplicationContext m_applicationContext;
    DcmPDUItemList m_acceptedPesentationContextsList;
    DcmPDUUserInfo m_userInfoPDU;
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmAAssociateAccept &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmAAssociateAccept &pdu);

#endif // DCMAASSOCIATEACCEPT_H
