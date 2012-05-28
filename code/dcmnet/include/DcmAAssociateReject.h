#ifndef DCMAASSOCIATEREJECT_H
#define DCMAASSOCIATEREJECT_H

#include "DcmPDUItem.h"
#include "DcmStream.h"
#include "DcmNetApi.h"

/*! Association rejection PDU.
 * This class described a PDU used to reject an association.
 */
class DCM_NET_API DcmAAssociateReject: public DcmPDUItem
{
public:

    DcmAAssociateReject();
    DcmAAssociateReject(DcmAssociationResultType result,
                        DcmAssociationSourceType source,
                        DcmAssociationReasonType reason);
    DcmAAssociateReject(const DcmAAssociateReject &pdu);
    DcmAAssociateReject& operator =(const DcmAAssociateReject &pdu);
    DcmPDUItem* clone() const;
    ~DcmAAssociateReject();

    DcmAssociationResultType result() const;
    void setResult(DcmAssociationResultType result);

    DcmAssociationSourceType source() const;
    void setSource(DcmAssociationSourceType source);

    DcmAssociationReasonType reason() const;
    void setReason(DcmAssociationReasonType reason);
    QString reasonAsString() const;

    DcmSize size() const;
    DcmSize contentSize() const;

    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmAAssociateReject &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmAAssociateReject &pdu);
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmAAssociateReject &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmAAssociateReject &pdu);

#endif // DCMAASSOCIATEREJECT_H
