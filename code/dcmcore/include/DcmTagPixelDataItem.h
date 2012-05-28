#ifndef DCMTAGPIXELDATAITEM_H
#define DCMTAGPIXELDATAITEM_H

#include "DcmCoreApi.h"
#include "DcmTagBinary.h"

/*! Pixel data item tag.
 * Pixel data tag may contain sequential information orgamized
 * as items. This class handles these items dedicated to pixel data.
 * The pixel data item tag is encoded using (fffe, e000) key,
 * however it does not contain another tags inside but raw binary
 * data used for image decompressing.
 */
class DCM_CORE_API DcmTagPixelDataItem: public DcmTagBinary
{
public:

    /**
     * Construct pixel data item tag.
     */
    DcmTagPixelDataItem();

    /**
     * Copy constructor.
     * \param item Pixel data item to be copied.
     */
    DcmTagPixelDataItem(const DcmTagPixelDataItem &item);

    /**
     * Assignment operator.
     * \param item Pixel data item to be assigned.
     * \return This item.
     */
    DcmTagPixelDataItem& operator =(const DcmTagPixelDataItem &item);

    /**
     * Clone this tag.
     * \return Pointer to the cloned tag.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagPixelDataItem();

    /**
     * Returns tag size in bytes for given transfer syntax.
     * \param transferSyntax Transfer syntax to encode data.
     * \return Tag size in bytes.
     */
    DcmSize size(const DcmTransferSyntax &transferSyntax) const;

};

#endif // DCMTAGPIXELDATAITEM_H
