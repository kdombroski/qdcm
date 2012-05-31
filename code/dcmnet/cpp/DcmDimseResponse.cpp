#include "DcmTagUS.h"
#include "DcmDimseResponse.h"

DcmDimseResponse::DcmDimseResponse()
    : DcmDimseMessage()
{
}

DcmDimseResponse::DcmDimseResponse(const DcmDataset &dataset)
    : DcmDimseMessage(dataset)
{
}

DcmDimseResponse::DcmDimseResponse(const DcmDimseRequest &request)
    : DcmDimseMessage()
{
    setServiceClassUID(request.serviceClassUID());
    setCommand(request.command());
    setResponseMessageId(request.messageId());
    setStatus(DcmDimseResponse::Status_Success);
}

DcmDimseResponse::DcmDimseResponse(const DcmDimseResponse &message)
    : DcmDimseMessage(message)
{
}

DcmDimseResponse& DcmDimseResponse::operator =(const DcmDimseResponse &message)
{
    if (this != &message) {
        DcmDimseMessage::operator =(message);
    }
    return *this;
}

DcmDimseMessage* DcmDimseResponse::clone() const
{
    return new DcmDimseResponse(*this);
}

DcmDimseResponse::Status DcmDimseResponse::status() const
{
    DcmTag *tag = constCommandDataset().findTag(DcmTagKey::CommandStatus);
    if (tag) {
        return (DcmDimseResponse::Status)tag->value().toInt();
    }
    return DcmDimseResponse::Status_Invalid;
}

void DcmDimseResponse::setStatus(DcmDimseResponse::Status s)
{
    DcmTagUS tag(DcmTagKey::CommandStatus);
    tag.setUnsignedShort((DcmUnsignedShort)s);
    commandDataset().insert(tag);
}

int DcmDimseResponse::responseMessageId() const
{
    return constCommandDataset().tagValue(DcmTagKey::CommandResponseMessageId).toInt();
}

void DcmDimseResponse::setResponseMessageId(int id)
{
    DcmTagUS tag(DcmTagKey::CommandResponseMessageId);
    tag.setUnsignedShort((DcmUnsignedShort)id);
    commandDataset().insert(tag);
}
