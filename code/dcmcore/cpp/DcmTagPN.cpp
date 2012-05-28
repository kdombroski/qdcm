#include "DcmTagPN.h"

DcmTagPN::DcmTagPN()
    : DcmTagString(DcmTagKey(), DcmVr::PN)
{
}

DcmTagPN::DcmTagPN(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::PN)
{
}

DcmTagPN::DcmTagPN(const DcmTagPN &tag)
    : DcmTagString(tag)
{
}

DcmTagPN& DcmTagPN::operator =(const DcmTagPN &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagPN::clone() const
{
    return new DcmTagPN(*this);
}

DcmTagPN::~DcmTagPN()
{
}

DcmTagPN& DcmTagPN::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
