#ifndef DCMPDUMAXLENGTH_H
#define DCMPDUMAXLENGTH_H

#include "DcmPDUItem.h"
#include "DcmStream.h"
#include "DcmNetApi.h"

/*! PDU maximal lenth item.
 * This PDU encodes the PDU maximal length in bytes
 * to be used in further data transfer.
 */
class DCM_NET_API DcmPDUMaxLength: public DcmPDUItem
{
public:

    static const DcmPDUMaxLength Default;   ///< Default size of 16384 bytes.

    /**
     * Construct PDU maximal length item.
     * \param length Maximal PDU length in bytes.
     */
    DcmPDUMaxLength(DcmSize length = 16384);

    /**
     * Copy constructor.
     * \param pdu PDU to be copied.
     */
    DcmPDUMaxLength(const DcmPDUMaxLength &pdu);

    /**
     * Assignment operator.
     * \param pdu PDU item to be assigned.
     * \return This PDU item.
     */
    DcmPDUMaxLength& operator =(const DcmPDUMaxLength &pdu);

    /**
     * Clone this PDU item.
     * \return Pointer to cloned PDU item.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmPDUMaxLength();

    /**
     * Returns maximal PDU length in bytes.
     * \return Maximal PDU length.
     */
    DcmSize length() const;

    /**
     * Returns this PDU item content size in bytes.
     * \return This PDU item content size.
     */
    DcmSize contentSize() const;

    /**
     * Tells whether this PDU item is valid.
     * \return Always true.
     */
    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmPDUMaxLength &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmPDUMaxLength &pdu);

private:

    DcmSize m_length;   ///< Maximal PDU length in bytes.
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmPDUMaxLength &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmPDUMaxLength &pdu);

#endif // DCMPDUMAXLENGTH_H
