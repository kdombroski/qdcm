#ifndef DCMTAGUT_H
#define DCMTAGUT_H

#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM Unlimited Text (UT) tag.
 *
 * This tag holds a text of an unlimited length.
 */
class DCM_CORE_API DcmTagUT: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagUT();

    /**
     * Construct an UT tag.
     * \param tagKey Tag key.
     */
    DcmTagUT(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagUT(const DcmTagUT &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagUT& operator =(const DcmTagUT &tag);

    /**
     * Clone this tag.
     * \return Pointer to this tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagUT();

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagUT& operator =(const QVariant &v);
};

#endif // DCMTAGUT_H
