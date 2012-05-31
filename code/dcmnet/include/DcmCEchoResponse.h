#ifndef DCMCECHORESPONSE_H
#define DCMCECHORESPONSE_H

#include "DcmDimseResponse.h"
#include "DcmCEchoRequest.h"
#include "DcmNetApi.h"

/*! DIMSE C-ECHO message response.
 * This class represents a C-ECHO response message.
 */
class DCM_NET_API DcmCEchoResponse: public DcmDimseResponse
{
public:

    /**
     * Default constructor.
     */
    DcmCEchoResponse();

    /**
     * Construct C-Echo response from command dataset.
     * \param dataset Command dataset.
     */
    DcmCEchoResponse(const DcmDataset &dataset);

    /**
     * Construct C-Echo response from request message.
     * \param request C-Echo request message.
     */
    DcmCEchoResponse(const DcmCEchoRequest &request);

    /**
     * Copy constructor.
     * \param message DIMSE message to be copied.
     */
    DcmCEchoResponse(const DcmCEchoResponse &message);

    /**
     * Assignment operator.
     * \param message DIMSE message to be assigned.
     * \return This DIMSE message.
     */
    DcmCEchoResponse& operator =(const DcmCEchoResponse &message);

    /**
     * Clone this DIMSE message.
     * \return Pointer to cloned message.
     */
    DcmDimseMessage* clone() const;
};

#endif // DCMCECHORESPONSE_H
