#include "DcmAReleaseResponse.h"

DcmAReleaseResponse::DcmAReleaseResponse()
    : DcmPDUItem(DcmPDUType_AReleaseRp)
{
}

DcmAReleaseResponse::DcmAReleaseResponse(const DcmAReleaseResponse &pdu)
    : DcmPDUItem(pdu)
{
}

DcmAReleaseResponse& DcmAReleaseResponse::operator =(const DcmAReleaseResponse &pdu)
{
    if (this != &pdu) {
        DcmPDUItem::operator =(pdu);
    }
    return *this;
}

DcmPDUItem* DcmAReleaseResponse::clone() const
{
    return new DcmAReleaseResponse(*this);
}

DcmAReleaseResponse::~DcmAReleaseResponse()
{
}

DcmSize DcmAReleaseResponse::size() const
{
    return 6 + contentSize();
}

DcmSize DcmAReleaseResponse::contentSize() const
{
    return 4;
}

bool DcmAReleaseResponse::isValid() const
{
    return true;
}

DcmStream& operator <<(DcmStream &stream, const DcmAReleaseResponse &pdu)
{
    char c[2] = {DcmPDUType_AReleaseRp, 0};
    DcmSize length = pdu.contentSize();

    stream.dataStream().writeRawData(c, 2);
    stream.writePDUSize32(length);
    length = 0;
    stream.writePDUSize32(length);

    return stream;
}

DcmStream& operator >>(DcmStream &stream, DcmAReleaseResponse &pdu)
{
    char c[2];

    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_AReleaseRp && c[1] == 0) {
        DcmSize length = stream.readPDUSize32();
        stream.dataStream().skipRawData(length);
    }

    return stream;
}

