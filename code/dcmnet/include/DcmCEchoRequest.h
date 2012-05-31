#ifndef DCMCECHOREQUEST_H
#define DCMCECHOREQUEST_H

#include "DcmDimseRequest.h"
#include "DcmNetApi.h"

/*! C-ECHO DIMSE request.
 * This class represents C-ECHO request.
 * C-ECHO request is sent to remote DICOM station in order
 * to verify DICOM connection. This DIMSE message does not
 * carry any additional data.
 */
class DCM_NET_API DcmCEchoRequest: public DcmDimseRequest
{
public:

    /**
     * Default constructor.
     */
    DcmCEchoRequest();

    /**
     * Construct C-ECHO request from command dataset.
     * \param dataset Command dataset.
     */
    DcmCEchoRequest(const DcmDataset &dataset);

    /**
     * Construct C-ECHO request via message id.
     * \param id Message id.
     */
    DcmCEchoRequest(int id);

    /**
     * Copy constructor.
     * \param message DIMSE message to be copied.
     */
    DcmCEchoRequest(const DcmCEchoRequest &message);

    /**
     * Assignment operator.
     * \param message DIMSE message to be assigned.
     * \return This DIMSE message.
     */
    DcmCEchoRequest& operator =(const DcmCEchoRequest &message);

    /**
     * Clone this DIMSE message.
     * \return Pointer to cloned message.
     */
    DcmDimseMessage* clone() const;
};

#endif // DCMCECHOREQUEST_H
