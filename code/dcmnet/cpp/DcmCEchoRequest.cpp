#include "DcmAbstractSyntax.h"
#include "DcmCEchoRequest.h"

DcmCEchoRequest::DcmCEchoRequest()
    : DcmDimseRequest(DcmAbstractSyntax::Verification.uid(), DcmCommandType_CEchoRequest)
{
}

DcmCEchoRequest::DcmCEchoRequest(const DcmDataset &dataset)
    : DcmDimseRequest(dataset)
{
}

DcmCEchoRequest::DcmCEchoRequest(int id)
    : DcmDimseRequest(DcmAbstractSyntax::Verification.uid(), DcmCommandType_CEchoRequest, id)
{

}

DcmCEchoRequest::DcmCEchoRequest(const DcmCEchoRequest &message)
    : DcmDimseRequest(message)
{
}

DcmCEchoRequest& DcmCEchoRequest::operator =(const DcmCEchoRequest &message)
{
    if (this != &message) {
        DcmDimseRequest::operator =(message);
    }
    return *this;
}

DcmDimseMessage* DcmCEchoRequest::clone() const
{
    return new DcmCEchoRequest(*this);
}
