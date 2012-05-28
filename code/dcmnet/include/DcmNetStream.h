#ifndef DCMNETSTREAM_H
#define DCMNETSTREAM_H

#include "DcmStream.h"
#include "DcmPDUItem.h"
#include "DcmNetApi.h"

/*! DICOM network I/O stream.
 * This class is a wrapper for DICOM stream class
 * that adds additional network I/O operations.
 */
class DCM_NET_API DcmNetStream
{
public:

    /**
     * Construct network stream.
     * \param stream Reference to DICOM stream.
     */
    DcmNetStream(DcmStream &stream);

    /**
     * Write PDU item to the stream.
     * \param item PDU item to be written.
     */
    void writePDUItem(const DcmPDUItem &item);

    /**
     * Read PDU item from the stream.
     * \return Pointer to an item read or null if failed to read.
     */
    DcmPDUItem* readPDUItem();

private:

    // No copy allowed
    Q_DISABLE_COPY(DcmNetStream)

    DcmStream *m_streamPtr; ///< Pointer to DICOM stream.

};

#endif // DCMNETSTREAM_H
