#include "DcmTagPixelDataItem.h"

DcmTagPixelDataItem::DcmTagPixelDataItem()
    : DcmTagBinary(DcmTagKey::Item, DcmVr::None)
{
}

DcmTagPixelDataItem::DcmTagPixelDataItem(const DcmTagPixelDataItem &item)
    : DcmTagBinary(item)
{
}

DcmTagPixelDataItem& DcmTagPixelDataItem::operator =(const DcmTagPixelDataItem &item)
{
    if (this != &item) {
        DcmTagBinary::operator =(item);
    }
    return *this;
}

DcmTag* DcmTagPixelDataItem::clone() const
{
    return new DcmTagPixelDataItem(*this);
}

DcmTagPixelDataItem::~DcmTagPixelDataItem()
{
}

DcmSize DcmTagPixelDataItem::size(const DcmTransferSyntax &transferSyntax) const
{
    // FF FE E0 00 <size, 4 bytes> = 8 bytes (always encoded as implicit)
    return contentSize(transferSyntax) + 8;
}
