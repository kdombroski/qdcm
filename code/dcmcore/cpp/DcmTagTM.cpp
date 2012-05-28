#include "DcmGlobal.h"
#include "DcmTagTM.h"

DcmTagTM::DcmTagTM()
    : DcmTagString(DcmTagKey(), DcmVr::TM)
{
}

DcmTagTM::DcmTagTM(const DcmTagKey &tagKey)
    : DcmTagString(tagKey, DcmVr::TM)
{
}

DcmTagTM::DcmTagTM(const DcmTagTM &tag)
    : DcmTagString(tag)
{
}

DcmTagTM& DcmTagTM::operator =(const DcmTagTM &tag)
{
    if (this != &tag) {
        DcmTagString::operator =(tag);
    }
    return *this;
}

DcmTag* DcmTagTM::clone() const
{
    return new DcmTagTM(*this);
}

DcmTagTM::~DcmTagTM()
{
}

void DcmTagTM::setValue(const QVariant &v)
{
    QString str;
    if (v.type() == QVariant::Time) {
        str = dcmTimeToString(v.toTime());
    } else {
        str = v.toString();
    }

    setString(str);
}

void DcmTagTM::appendValue(const QVariant &v)
{
    QString str;
    if (v.type() == QVariant::Time) {
        str = dcmTimeToString(v.toTime());
    } else {
        str = v.toString();
    }

    appendString(str);
}

DcmTagTM& DcmTagTM::operator =(const QVariant &v)
{
    setValue(v);
    return *this;
}

QTime DcmTagTM::asTime() const
{
    QString str = asString().left(16);

    int idx = asString().indexOf("\\");
    if (idx != -1) {
        str = str.left(idx);
    }

    return dcmStringToTime(str);
}

QList<QTime> DcmTagTM::asTimeList() const
{
    QStringList sl = asStringList();
    QList<QTime> tl;

    foreach (QString s, sl) {
        tl.append(dcmStringToTime(s));
    }

    return tl;
}

void DcmTagTM::setTime(const QTime &time)
{
    setString(dcmTimeToString(time));
}

void DcmTagTM::appendTime(const QTime &time)
{
    appendString(dcmTimeToString(time));
}
