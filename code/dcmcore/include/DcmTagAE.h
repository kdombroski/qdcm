#ifndef DCMTAGAE_H
#define DCMTAGAE_H

#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM Application Entity (AE) tag.
 *
 * This tag keeps a name of DICOM application entity,
 * which is an identifier of DICOM node.
 */
class DCM_CORE_API DcmTagAE: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagAE();

    /**
     * Construct an AE tag.
     * \param tagKey Tag key.
     */
    DcmTagAE(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagAE(const DcmTagAE &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagAE& operator =(const DcmTagAE &tag);

    /**
     * Clone this tag.
     * \return Pointer to this tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagAE();

    /**
     * Assign value.
     * \param v Value to be assigned.
     * \return This tag.
     */
    DcmTagAE& operator =(const QVariant &v);
};

#endif // DCMTAGAE_H
