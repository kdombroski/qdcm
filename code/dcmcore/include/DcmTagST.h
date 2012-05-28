#ifndef DCMTAGST_H
#define DCMTAGST_H

#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM Short Text (ST) tag.
 *
 * The ST tag encodes a text string of 1024 symbols maximum.
 */
class DCM_CORE_API DcmTagST: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagST();

    /**
     * Construct an ST tag.
     * \param tagKey Tag key.
     */
    DcmTagST(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagST(const DcmTagST &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagST& operator =(const DcmTagST &tag);

    /**
     * Clone this tag.
     * \return Pointer to a cloned tag.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagST();

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagST& operator =(const QVariant &v);
};

#endif // DCMTAGST_H
