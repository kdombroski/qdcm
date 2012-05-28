#include "DcmPDUMaxLength.h"

const DcmPDUMaxLength DcmPDUMaxLength::Default(16384);

DcmPDUMaxLength::DcmPDUMaxLength(DcmSize length)
    : DcmPDUItem(DcmPDUType_PDUMaxLength),
      m_length(length)
{
    Q_ASSERT(length > 0);
}

DcmPDUMaxLength::DcmPDUMaxLength(const DcmPDUMaxLength &pdu)
    : DcmPDUItem(pdu),
      m_length(pdu.m_length)
{
}

DcmPDUMaxLength& DcmPDUMaxLength::operator =(const DcmPDUMaxLength &pdu)
{
    if (this != &pdu) {
        DcmPDUItem::operator =(pdu);
        m_length = pdu.m_length;
    }
    return *this;
}

DcmPDUItem* DcmPDUMaxLength::clone() const
{
    return new DcmPDUMaxLength(*this);
}

DcmPDUMaxLength::~DcmPDUMaxLength()
{
}

DcmSize DcmPDUMaxLength::length() const
{
    return m_length;
}

DcmSize DcmPDUMaxLength::contentSize() const
{
    return 4; // sizeof(DcmSize)
}

bool DcmPDUMaxLength::isValid() const
{
    return true;
}

DcmStream& operator <<(DcmStream &stream, const DcmPDUMaxLength &pdu)
{
    char c[2] = {DcmPDUType_PDUMaxLength, 0};
    DcmUnsignedShort length = pdu.contentSize();
    DcmSize pduMaxLength = pdu.length();

    stream.dataStream().writeRawData(c, 2);
    stream.writePDUSize16(length);
    stream.writePDUSize32(pduMaxLength);

    return stream;
}

DcmStream& operator >>(DcmStream &stream, DcmPDUMaxLength &pdu)
{
    char c[2];
    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_PDUMaxLength && c[1] == 0) {
        DcmUnsignedShort length;
        DcmSize pduMaxLength;

        length = stream.readPDUSize16();
        pduMaxLength = stream.readPDUSize32();

        pdu = DcmPDUMaxLength(pduMaxLength);
    }

    return stream;
}
