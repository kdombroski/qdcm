#ifndef DCMARELEASEREQUEST_H
#define DCMARELEASEREQUEST_H

#include "DcmPDUItem.h"
#include "DcmStream.h"
#include "DcmNetApi.h"

/*! DICOM association release PDU.
 * This class defines an association release PDU item.
 * The association release request PDU does not have any
 * particular parameters.
 */
class DCM_NET_API DcmAReleaseRequest: public DcmPDUItem
{
public:

    /**
     * Construct association release PDU.
     */
    DcmAReleaseRequest();

    /**
     * Copy cnstructor.
     * \param pdu PDU item to be copied.
     */
    DcmAReleaseRequest(const DcmAReleaseRequest &pdu);

    /**
     * Assignment oerator.
     * \param pdu PDU item to be set.
     * \return This PDU item.
     */
    DcmAReleaseRequest& operator =(const DcmAReleaseRequest &pdu);

    /**
     * Clone this PDU item.
     * \return Pointer to cloned PDU item.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmAReleaseRequest();

    /**
     * Returns this PDU item size in bytes.
     * \return This PDU size.
     */
    DcmSize size() const;

    /**
     * Returns this PDU item content size in bytes.
     * \return This PDU content size.
     */
    DcmSize contentSize() const;

    /**
     * Tells whether this PDU is valid.
     * Association release PDU is always valid.
     * \return true.
     */
    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmAReleaseRequest &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmAReleaseRequest &pdu);
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmAReleaseRequest &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmAReleaseRequest &pdu);

#endif // DCMARELEASEREQUEST_H
