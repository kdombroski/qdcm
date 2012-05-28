#include "DcmAReleaseRequest.h"

DcmAReleaseRequest::DcmAReleaseRequest()
    : DcmPDUItem(DcmPDUType_AReleaseRq)
{
}

DcmAReleaseRequest::DcmAReleaseRequest(const DcmAReleaseRequest &pdu)
    : DcmPDUItem(pdu)
{
}

DcmAReleaseRequest& DcmAReleaseRequest::operator =(const DcmAReleaseRequest &pdu)
{
    if (this != &pdu) {
        DcmPDUItem::operator =(pdu);
    }
    return *this;
}

DcmPDUItem* DcmAReleaseRequest::clone() const
{
    return new DcmAReleaseRequest(*this);
}

DcmAReleaseRequest::~DcmAReleaseRequest()
{
}

DcmSize DcmAReleaseRequest::size() const
{
    return 6 + contentSize();
}

DcmSize DcmAReleaseRequest::contentSize() const
{
    return 4;
}

bool DcmAReleaseRequest::isValid() const
{
    return true;
}

DcmStream& operator <<(DcmStream &stream, const DcmAReleaseRequest &pdu)
{
    char c[2] = {DcmPDUType_AReleaseRq, 0};
    DcmSize length = pdu.contentSize();

    stream.dataStream().writeRawData(c, 2);
    stream.writePDUSize32(length);
    length = 0;
    stream.writePDUSize32(length);

    return stream;
}

DcmStream& operator >>(DcmStream &stream, DcmAReleaseRequest &pdu)
{
    char c[2];

    stream.dataStream().readRawData(c, 2);
    if (c[0] == DcmPDUType_AReleaseRq && c[1] == 0) {
        DcmSize length = stream.readPDUSize32();
        stream.dataStream().skipRawData(length);
    }

    return stream;
}

