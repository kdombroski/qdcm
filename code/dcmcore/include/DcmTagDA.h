#ifndef DCMTAGDA_H
#define DCMTAGDA_H

#include <QList>
#include <QDate>
#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM Date (DA) tag.
 *
 * This tag holds date value encoded in string format:
 * "YYYYMMDD".
 */
class DCM_CORE_API DcmTagDA: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagDA();

    /**
     * Construct a DA tag.
     * \param tagKey Tag key.
     */
    DcmTagDA(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagDA(const DcmTagDA &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagDA& operator =(const DcmTagDA &tag);

    /**
     * Clone this tag.
     * \return Pointer to the tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagDA();

    /**
     * Assign value to this tag.
     * This method takes string and date values.
     * For string values the verification is performed.
     * \param v Value to be set.
     */
    void setValue(const QVariant &v);

    /**
     * Append a value to the list of values.
     * This method takes string or date values.
     * For string values the verification is performed.
     * \param v Value to be added.
     */
    void appendValue(const QVariant &v);

    /**
     * Assign value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagDA& operator =(const QVariant &v);

    /**
     * Returns the tag value as date type.
     * For tags with multiplicity > 1 this method
     * returns the very first value only.
     * \return Tag's value in date format.
     */
    QDate asDate() const;

    /**
     * Returns tag value as a list of dates.
     * \return List of dates.
     */
    QList<QDate> asDatesList() const;

    /**
     * Set date value.
     * \param date Date to be set.
     */
    void setDate(const QDate &date);

    /**
     * Append a date value to the list of values.
     * \param date Date to be added.
     */
    void appendDate(const QDate &date);
};

#endif // DCMTAGDA_H
