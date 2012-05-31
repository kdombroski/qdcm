#include "DcmDimseRequest.h"

DcmDimseRequest::DcmDimseRequest()
    : DcmDimseMessage()
{
}

DcmDimseRequest::DcmDimseRequest(const DcmDataset &dataset)
    : DcmDimseMessage(dataset)
{
}

DcmDimseRequest::DcmDimseRequest(const QString &serviceClassUID, DcmCommandType command, int id)
    : DcmDimseMessage(serviceClassUID, command, id)
{
}

DcmDimseRequest::DcmDimseRequest(const DcmDimseRequest &message)
    : DcmDimseMessage(message)
{
}

DcmDimseRequest& DcmDimseRequest::operator =(const DcmDimseRequest &message)
{
    if (this != &message) {
        DcmDimseMessage::operator =(message);
    }
    return *this;
}

DcmDimseMessage* DcmDimseRequest::clone() const
{
    return new DcmDimseRequest(*this);
}
