#include "DcmTagST.h"

DcmTagST::DcmTagST()
    : DcmTagString(DcmTagKey(), DcmVr::ST)
{
}

DcmTagST::DcmTagST(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::ST)
{
}

DcmTagST::DcmTagST(const DcmTagST &tag)
    : DcmTagString(tag)
{
}

DcmTagST& DcmTagST::operator =(const DcmTagST &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagST::clone() const
{
    return new DcmTagST(*this);
}

DcmTagST::~DcmTagST()
{
}

DcmTagST& DcmTagST::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
