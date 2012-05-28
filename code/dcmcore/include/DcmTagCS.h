#ifndef DCMTAGCS_H
#define DCMTAGCS_H

#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! Code String (CS) tag.
 *
 * A string of upper-case characters (16 max).
 */
class DCM_CORE_API DcmTagCS: public DcmTagString
{
public:

    /**
     * Default constructor.
     * Constructs CS tag with no value and zero tag key.
     */
    DcmTagCS();

    /**
     * Construct CS tag with no value.
     * \param tagKey Tag key.
     */
    DcmTagCS(const DcmTagKey &tagKey);

    /**
     * Copy ocnstructor.
     * \param tag Tag to be copied.
     */
    DcmTagCS(const DcmTagCS &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagCS& operator =(const DcmTagCS &tag);

    /**
     * Clone this tag.
     * \return Pointer to cloned tag
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagCS();

    /**
     * Assign tag value.
     * The CS value is trimmed and transformed to upper case.
     * \param v Value to be assigned.
     */
    void setValue(const QVariant &v);

    /**
     * Append value.
     * The value is trimmed and transformed to upper case.
     * \param v Value to be added.
     */
    void appendValue(const QVariant &v);

    /**
     * Assign value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagCS& operator =(const QVariant &v);
};

#endif // DCMTAGCS_H
