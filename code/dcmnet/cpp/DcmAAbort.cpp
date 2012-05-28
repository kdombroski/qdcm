#include "DcmAAbort.h"

DcmAAbort::DcmAAbort()
    : DcmPDUItem(DcmPDUType_AAbort),
      m_source(DcmAssociationSourceType_ServiceProvider),
      m_reason(DcmAssociationReasonType_NoReason)
{
}

DcmAAbort::DcmAAbort(DcmAssociationSourceType source, DcmAssociationReasonType reason)
    : DcmPDUItem(DcmPDUType_AAbort),
      m_source(source),
      m_reason(reason)
{
}

DcmAAbort::DcmAAbort(const DcmAAbort &pdu)
    : DcmPDUItem(pdu),
      m_source(pdu.m_source),
      m_reason(pdu.m_reason)
{
}

DcmAAbort& DcmAAbort::operator =(const DcmAAbort &pdu)
{
    if (this != &pdu) {
        DcmPDUItem::operator =(pdu);
        m_source = pdu.m_source;
        m_reason = pdu.m_reason;
    }
    return *this;
}

DcmPDUItem* DcmAAbort::clone() const
{
    return new DcmAAbort(*this);
}

DcmAAbort::~DcmAAbort()
{
}

DcmAssociationSourceType DcmAAbort::source() const
{
    return m_source;
}

void DcmAAbort::setSource(DcmAssociationSourceType src)
{
    m_source = src;
}

DcmAssociationReasonType DcmAAbort::reason() const
{
    return m_reason;
}

void DcmAAbort::setReason(DcmAssociationReasonType r)
{
    m_reason = r;
}

DcmSize DcmAAbort::contentSize() const
{
    return 4;
}

DcmSize DcmAAbort::size() const
{
    return 6 + contentSize();
}

bool DcmAAbort::isValid() const
{
    return true;
}

DcmStream& operator <<(DcmStream &stream, const DcmAAbort &pdu)
{
    char c[2] = {DcmPDUType_AAbort, 0};
    stream.dataStream().writeRawData(c, 2);
    DcmSize length = pdu.contentSize();
    stream.writePDUSize32(length);

    char cc[4];
    cc[0] = 0;
    cc[1] = 0;
    cc[2] = (char)pdu.source();
    cc[3] = (char)pdu.reason();

    stream.dataStream().writeRawData(cc, 4);

    return stream;
}

DcmStream& operator >>(DcmStream &stream, DcmAAbort &pdu)
{
    char c[2];

    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_AAbort && c[1] == 0) {
        DcmSize length = stream.readPDUSize32();
        if (length == 4) {
            char cc[4];
            stream.dataStream().readRawData(cc, 4);

            pdu.setSource((DcmAssociationSourceType)cc[2]);
            pdu.setReason((DcmAssociationReasonType)cc[3]);
        }
    }

    return stream;
}
