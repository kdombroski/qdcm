#include "DcmAbstractSyntax.h"
#include "DcmCEchoResponse.h"

DcmCEchoResponse::DcmCEchoResponse()
    : DcmDimseResponse()
{
    setServiceClassUID(DcmAbstractSyntax::Verification.uid());
    setCommand(DcmCommandType_CEchoResponse);
    setMessageId(0);
    setStatus(DcmDimseResponse::Status_Success);
}

DcmCEchoResponse::DcmCEchoResponse(const DcmDataset &dataset)
    : DcmDimseResponse(dataset)
{
}

DcmCEchoResponse::DcmCEchoResponse(const DcmCEchoRequest &request)
    : DcmDimseResponse(request)
{
}

DcmCEchoResponse::DcmCEchoResponse(const DcmCEchoResponse &message)
    : DcmDimseResponse(message)
{
}

DcmCEchoResponse& DcmCEchoResponse::operator =(const DcmCEchoResponse &message)
{
    if (this != &message) {
        DcmDimseResponse::operator =(message);
    }
    return *this;
}

DcmDimseMessage* DcmCEchoResponse::clone() const
{
    return new DcmCEchoResponse(*this);
}
