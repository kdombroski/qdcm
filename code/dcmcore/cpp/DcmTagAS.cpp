#include <QDebug>
#include "DcmGlobal.h"
#include "DcmTagAS.h"

DcmTagAS::DcmTagAS()
    : DcmTagString(DcmTagKey(), DcmVr::AS)
{
}

DcmTagAS::DcmTagAS(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::AS)
{
}

DcmTagAS::DcmTagAS(const DcmTagAS &tag)
    : DcmTagString(tag)
{
}

DcmTagAS& DcmTagAS::operator =(const DcmTagAS &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagAS::clone() const
{
    return new DcmTagAS(*this);
}

DcmTagAS::~DcmTagAS()
{
}

void DcmTagAS::setValue(const QVariant &v)
{
    QString str = v.toString().trimmed();

    if (!dcmIsValidAgeString(str)) {
        qCritical() << "The age string value" << str << "is invalid.";
    }

    setString(str);
}

void DcmTagAS::appendValue(const QVariant &v)
{
    QString str = v.toString().trimmed();

    if (!dcmIsValidAgeString(str)) {
        qCritical() << "The age string value" << str << "is invalid.";
    }

    appendString(str);
}

DcmTagAS& DcmTagAS::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}
