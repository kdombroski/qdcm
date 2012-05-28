#include "DcmTagLO.h"

DcmTagLO::DcmTagLO()
    : DcmTagString(DcmTagKey(), DcmVr::LO)
{
}

DcmTagLO::DcmTagLO(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::LO)
{
}

DcmTagLO::DcmTagLO(const DcmTagLO &tag)
    : DcmTagString(tag)
{
}

DcmTagLO& DcmTagLO::operator =(const DcmTagLO &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagLO::clone() const
{
    return new DcmTagLO(*this);
}

DcmTagLO::~DcmTagLO()
{
}

DcmTagLO& DcmTagLO::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
