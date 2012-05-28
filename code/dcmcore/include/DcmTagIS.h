#ifndef DCMTAGIS_H
#define DCMTAGIS_H

#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM Integer String (IS) tag.
 *
 * A string of characters representing an integer.
 */
class DCM_CORE_API DcmTagIS: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagIS();

    /**
     * Construct IS tag.
     * \param tagKey Tag key.
     */
    DcmTagIS(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagIS(const DcmTagIS &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagIS& operator =(const DcmTagIS &tag);

    /**
     * Clone this tag.
     * \return Pointer to the tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagIS();

    /**
     * Assign value of the tag.
     * This method takes integer or string values.
     * \param v Value to be assigned.
     */
    void setValue(const QVariant &v);

    /**
     * Append a value.
     * This method takes integer or string values.
     * \param v Value to be added.
     */
    void appendValue(const QVariant &v);

    /**
     * Returns tag value as integer.
     * \return Tag value.
     */
    int asInt() const;

    /**
     * Returns tag value as list of integers.
     * \return List of values.
     */
    QList<int> asIntList() const;

    /**
     * Assign tag value.
     * \param v Value to be assigned.
     */
    void setInt(int v);

    /**
     * Append value.
     * \param v Value to be added.
     */
    void appendInt(int v);
};

#endif // DCMTAGIS_H
