#include "DcmTagCS.h"

DcmTagCS::DcmTagCS()
    : DcmTagString(DcmTagKey(), DcmVr::CS)
{
}

DcmTagCS::DcmTagCS(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::CS)
{
}

DcmTagCS::DcmTagCS(const DcmTagCS &tag)
    : DcmTagString(tag)
{
}

DcmTagCS& DcmTagCS::operator =(const DcmTagCS &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagCS::clone() const
{
    return new DcmTagCS(*this);
}

DcmTagCS::~DcmTagCS()
{
}

void DcmTagCS::setValue(const QVariant &v)
{
    setString(v.toString().toUpper());
}

void DcmTagCS::appendValue(const QVariant &v)
{
    appendString(v.toString().toUpper());
}

DcmTagCS& DcmTagCS::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
