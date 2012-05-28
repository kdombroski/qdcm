#include <QDebug>
#include "DcmGlobal.h"
#include "DcmTagDA.h"

DcmTagDA::DcmTagDA()
    : DcmTagString(DcmTagKey(), DcmVr::DA)
{
}

DcmTagDA::DcmTagDA(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::DA)
{
}

DcmTagDA::DcmTagDA(const DcmTagDA &tag)
    : DcmTagString(tag)
{
}

DcmTagDA& DcmTagDA::operator =(const DcmTagDA &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagDA::clone() const
{
    return new DcmTagDA(*this);
}

DcmTagDA::~DcmTagDA()
{
}

void DcmTagDA::setValue(const QVariant &v)
{
    QString str;
    if (v.type() == QVariant::Date) {
        str = dcmDateToString(v.toDate());
    } else {
        str = v.toString().trimmed();
    }

    setString(str);
}

void DcmTagDA::appendValue(const QVariant &v)
{
    QString str;
    if (v.type() == QVariant::Date) {
        str = dcmDateToString(v.toDate());
    } else {
        str = v.toString().trimmed();
    }

    appendString(str);
}

DcmTagDA& DcmTagDA::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

QDate DcmTagDA::asDate() const
{
    return dcmStringToDate(asString());
}

QList<QDate> DcmTagDA::asDatesList() const
{
    QStringList sl = asStringList();
    QList<QDate> dl;

    foreach(QString s, sl) {
        dl.append(dcmStringToDate(s));
    }

    return dl;
}

void DcmTagDA::setDate(const QDate &date)
{
    setString(dcmDateToString(date));
}

void DcmTagDA::appendDate(const QDate &date)
{
    appendString(dcmDateToString(date));
}
