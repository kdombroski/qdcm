#include "DcmGlobal.h"
#include "DcmPDUImplementationClassUID.h"

DcmPDUImplementationClassUID::DcmPDUImplementationClassUID()
    : DcmPDUItem(DcmPDUType_ImplementationClassUID),
      m_uid()
{
}

DcmPDUImplementationClassUID::DcmPDUImplementationClassUID(const QString &uid)
    : DcmPDUItem(DcmPDUType_ImplementationClassUID),
      m_uid(uid)
{
    Q_ASSERT(dcmIsValidUID(uid));
}

DcmPDUImplementationClassUID::DcmPDUImplementationClassUID(const DcmPDUImplementationClassUID &pdu)
    : DcmPDUItem(pdu),
      m_uid(pdu.m_uid)
{
}

DcmPDUImplementationClassUID& DcmPDUImplementationClassUID::operator =(const DcmPDUImplementationClassUID &pdu)
{
    if (this != &pdu) {
        DcmPDUItem::operator =(pdu);
        m_uid = pdu.m_uid;
    }
    return *this;
}

DcmPDUItem* DcmPDUImplementationClassUID::clone() const
{
    return new DcmPDUImplementationClassUID(*this);
}

DcmPDUImplementationClassUID::~DcmPDUImplementationClassUID()
{
}

QString DcmPDUImplementationClassUID::uid() const
{
    return m_uid;
}

DcmSize DcmPDUImplementationClassUID::contentSize() const
{
    return m_uid.length();
}

bool DcmPDUImplementationClassUID::isValid() const
{
    return !m_uid.isEmpty();
}

DcmStream& operator <<(DcmStream &stream, const DcmPDUImplementationClassUID &pdu)
{
    char c[2] = {DcmPDUType_ImplementationClassUID, 0};
    DcmUnsignedShort length = pdu.contentSize();

    stream.dataStream().writeRawData(c, 2);
    stream.writePDUSize16(length);

    stream.dataStream().writeRawData(pdu.m_uid.toAscii(), length);

    return stream;
}

DcmStream& operator >>(DcmStream &stream, DcmPDUImplementationClassUID &pdu)
{
    char c[2];
    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_ImplementationClassUID && c[1] == 0) {
        DcmUnsignedShort length = stream.readPDUSize16();

        char *buffer = new char[length];
        stream.dataStream().readRawData(buffer, length);
        QString uid = QString::fromAscii(buffer, length);
        delete[] buffer;

        pdu = DcmPDUImplementationClassUID(uid);
    }
    return stream;
}

