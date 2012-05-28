#include "DcmTagAE.h"

DcmTagAE::DcmTagAE()
    : DcmTagString(DcmTagKey(), DcmVr::AE)
{
}

DcmTagAE::DcmTagAE(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::AE)
{
}

DcmTagAE::DcmTagAE(const DcmTagAE &tag)
    : DcmTagString(tag)
{
}

DcmTagAE& DcmTagAE::operator =(const DcmTagAE &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagAE::clone() const
{
    return new DcmTagAE(*this);
}

DcmTagAE::~DcmTagAE()
{
}

DcmTagAE& DcmTagAE::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
