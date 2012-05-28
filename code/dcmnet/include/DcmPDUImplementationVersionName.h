#ifndef DCMPDUIMPLEMENTATIONVERSIONNAME_H
#define DCMPDUIMPLEMENTATIONVERSIONNAME_H

#include "DcmPDUItem.h"
#include "DcmStream.h"
#include "DcmNetApi.h"

/*! Implementation version name PDU item.
 * This PDU item encodes a DICOM communicator implementation version name
 * as a string.
 */
class DCM_NET_API DcmPDUImplementationVersionName: public DcmPDUItem
{
public:

    /**
     * Construct void imlementation version name.
     */
    DcmPDUImplementationVersionName();

    /**
     * Construct implementation version name.
     * \param name Version name.
     */
    DcmPDUImplementationVersionName(const QString &name);

    /**
     * Copy constructor.
     * \param pdu PDU to be copied.
     */
    DcmPDUImplementationVersionName(const DcmPDUImplementationVersionName &pdu);

    /**
     * Assignment operator.
     * \param pdu PDU to be assigned.
     * \return This PDU.
     */
    DcmPDUImplementationVersionName& operator =(const DcmPDUImplementationVersionName &pdu);

    /**
     * Clone this PDU item.
     * \return Pointer to cloned PDU.
     */
    DcmPDUItem* clone() const;

    /**
     * Destructor.
     */
    ~DcmPDUImplementationVersionName();

    /**
     * Returns implementation version name.
     * \return Version name.
     */
    QString name() const;

    /**
     * Returns PDU item content size in bytes.
     * \return This PDU item content size.
     */
    DcmSize contentSize() const;

    /**
     * Tells whether this PDU is valid.
     * This PDU is valid if version name is not empty.
     */
    bool isValid() const;

    // I/O operations
    DCM_NET_API friend DcmStream& operator <<(DcmStream &stream, const DcmPDUImplementationVersionName &pdu);
    DCM_NET_API friend DcmStream& operator >>(DcmStream &stream, DcmPDUImplementationVersionName &pdu);

private:

    QString m_name;
};

DCM_NET_API DcmStream& operator <<(DcmStream &stream, const DcmPDUImplementationVersionName &pdu);
DCM_NET_API DcmStream& operator >>(DcmStream &stream, DcmPDUImplementationVersionName &pdu);

#endif // DCMPDUIMPLEMENTATIONVERSIONNAME_H
