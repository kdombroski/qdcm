#include "DcmGlobal.h"
#include "DcmTagDT.h"

DcmTagDT::DcmTagDT()
    : DcmTagString(DcmTagKey(), DcmVr::DT)
{
}

DcmTagDT::DcmTagDT(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::DT)
{
}

DcmTagDT::DcmTagDT(const DcmTagDT &tag)
    : DcmTagString(tag)
{
}

DcmTagDT& DcmTagDT::operator =(const DcmTagDT &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagDT::clone() const
{
    return new DcmTagDT(*this);
}

DcmTagDT::~DcmTagDT()
{
}

void DcmTagDT::setValue(const QVariant &v)
{
    QString str;
    if (v.type() == QVariant::DateTime) {
        str = dcmDateTimeToString(v.toDateTime());
    } else {
        str = v.toString();
    }

    setString(str);
}

void DcmTagDT::appendValue(const QVariant &v)
{
    QString str;
    if (v.type() == QVariant::DateTime) {
        str = dcmDateTimeToString(v.toDateTime());
    } else {
        str = v.toString();
    }

    appendString(str);
}

DcmTagDT& DcmTagDT::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

QDateTime DcmTagDT::asDateTime() const
{
    QString str = asString().left(26);
    int idx = asString().indexOf("\\");
    if (idx != -1) {
        str = str.left(idx);
    }

    return dcmStringToDateTime(str);
}

QList<QDateTime> DcmTagDT::asDateTimeList() const
{
    QStringList sl = asStringList();
    QList<QDateTime> dtl;

    foreach (QString s, sl) {
        dtl.append(dcmStringToDateTime(s));
    }

    return dtl;
}

void DcmTagDT::setDateTime(const QDateTime &dateTime)
{
    setString(dcmDateTimeToString(dateTime));
}

void DcmTagDT::appendDateTime(const QDateTime &dateTime)
{
    appendString(dcmDateTimeToString(dateTime));
}
