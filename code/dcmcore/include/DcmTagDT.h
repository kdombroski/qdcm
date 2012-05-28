#ifndef DCMTAGDT_H
#define DCMTAGDT_H

#include <QDateTime>
#include <QList>
#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM Date & Time (DT) tag.
 *
 * This tag holds date and time value in string format:
 * YYYYMMDDHHMMSS.FRAC
 * Second's fraction can go as small as 1 microsecond.
 */
class DCM_CORE_API DcmTagDT: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagDT();

    /**
     * Construct a DT tag.
     * \param tagKey Tag key.
     */
    DcmTagDT(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     */
    DcmTagDT(const DcmTagDT &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagDT& operator =(const DcmTagDT &tag);

    /**
     * Clone this tag.
     * \return Clone of this tag.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagDT();

    /**
     * Assign value.
     * This method handles string or DateTime types.
     * \param v Value to be assigned.
     */
    void setValue(const QVariant &v);

    /**
     * Append value.
     * This method handles string or DateTime types.
     * \param v Value to be added.
     */
    void appendValue(const QVariant &v);

    /**
     * Assign value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagDT& operator =(const QVariant &v);

    /**
     * Returns tag value in DateTime format.
     * As Qt time precision is limited to one millisecond,
     * this may cause the precision loss.
     * Manipulate this tag in string format for higher precision.
     */
    QDateTime asDateTime() const;

    /**
     * Returns a list of DateTime values.
     * \return List of DateTime values.
     */
    QList<QDateTime> asDateTimeList() const;

    /**
     * Assign tag value in DateTime format.
     * \param dateTime Date/Time to be set.
     */
    void setDateTime(const QDateTime &dateTime);

    /**
     * Append DateTime value.
     * \param dateTime Date/Time to be added.
     */
    void appendDateTime(const QDateTime &dateTime);
};

#endif // DCMTAGDT_H
