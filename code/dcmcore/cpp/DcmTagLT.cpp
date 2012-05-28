#include "DcmTagLT.h"

DcmTagLT::DcmTagLT()
    : DcmTagString(DcmTagKey(), DcmVr::LT)
{
}

DcmTagLT::DcmTagLT(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::LT)
{
}

DcmTagLT::DcmTagLT(const DcmTagLT &tag)
    : DcmTagString(tag)
{
}

DcmTagLT& DcmTagLT::operator =(const DcmTagLT &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagLT::clone() const
{
    return new DcmTagLT(*this);
}

DcmTagLT::~DcmTagLT()
{
}

DcmTagLT& DcmTagLT::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
