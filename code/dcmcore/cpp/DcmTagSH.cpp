#include "DcmTagSH.h"

DcmTagSH::DcmTagSH()
    : DcmTagString(DcmTagKey(), DcmVr::SH)
{
}

DcmTagSH::DcmTagSH(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::SH)
{
}

DcmTagSH::DcmTagSH(const DcmTagSH &tag)
    : DcmTagString(tag)
{
}

DcmTagSH& DcmTagSH::operator =(const DcmTagSH &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagSH::clone() const
{
    return new DcmTagSH(*this);
}

DcmTagSH::~DcmTagSH()
{
}

DcmTagSH& DcmTagSH::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
