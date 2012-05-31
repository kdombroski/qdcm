#include "DcmTagUS.h"
#include "DcmDimsePriorityRequest.h"

DcmDimsePriorityRequest::DcmDimsePriorityRequest()
    : DcmDimseRequest()
{
    setPriority(DcmPriorityType_Medium);
}

DcmDimsePriorityRequest::DcmDimsePriorityRequest(const DcmDataset &dataset)
    : DcmDimseRequest(dataset)
{
}

DcmDimsePriorityRequest::DcmDimsePriorityRequest(const QString &serviceClassUID, DcmCommandType command, int id)
    : DcmDimseRequest(serviceClassUID, command, id)
{
    setPriority(DcmPriorityType_Medium);
}

DcmDimsePriorityRequest::DcmDimsePriorityRequest(const DcmDimsePriorityRequest &message)
    : DcmDimseRequest(message)
{
}

DcmDimsePriorityRequest& DcmDimsePriorityRequest::operator =(const DcmDimsePriorityRequest &message)
{
    if (this != &message) {
        DcmDimseRequest::operator =(message);
    }
    return *this;
}

DcmDimseMessage* DcmDimsePriorityRequest::clone() const
{
    return new DcmDimsePriorityRequest(*this);
}

DcmPriorityType DcmDimsePriorityRequest::priority() const
{
    DcmPriorityType p = DcmPriorityType_Medium;

    DcmTag *tag = constCommandDataset().findTag(DcmTagKey::CommandPriority);
    if (tag) {
        p = (DcmPriorityType)tag->value().toInt();
    }

    return p;
}

void DcmDimsePriorityRequest::setPriority(DcmPriorityType priority)
{
    DcmTagUS tag(DcmTagKey::CommandPriority);
    tag.setUnsignedShort((DcmUnsignedShort)priority);
    commandDataset().insert(tag);
}
