#ifndef DCMTAGBINARY_H
#define DCMTAGBINARY_H

#include <QByteArray>
#include <QVector>

#include "DcmCoreApi.h"
#include "DcmTag.h"

/*! Base class for binary-based tags.
 *
 * This class is a basis for binary tags OB, OW, OF, and UN.
 * Binary tag has always multiplicity of 1.
 */
class DCM_CORE_API DcmTagBinary: public DcmTag
{
public:

    /**
     * Default constructor.
     * Constructs an invalid binary tag.
     */
    DcmTagBinary();

    /**
     * Construct a binary tag.
     * If value representation is not binary, an invalid tag
     * will be constructed.
     * \param tagKey Tag key.
     * \param vr Value representation.
     */
    DcmTagBinary(const DcmTagKey &tagKey, const DcmVr &vr);

    /**
     * Copy ocnstructor.
     * \param tag Tag to be copied.
     */
    DcmTagBinary(const DcmTagBinary &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     */
    DcmTagBinary& operator =(const DcmTagBinary &tag);

    /**
     * Clone this tag.
     * \return Pointer to this tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagBinary();

    /**
     * Returns value of this tag.
     * \return Binary byte array encoded into variant.
     */
    QVariant value() const;

    /**
     * Returns list of tag's values.
     * For binary data values list consists of a single element,
     * which is binary byte array.
     * \return Values list.
     */
    QVariantList values() const;

    /**
     * Assign tag's value.
     * This method handles byte array values.
     * \param v Value to be assigned.
     */
    void setValue(const QVariant &v);

    /**
     * Append value.
     * This method handles byte array values.
     * The byte array will be concatenated to the current
     * byte array. Tag's multiplicity remains 1.
     * \param v Value to be added.
     */
    void appendValue(const QVariant &v);

    /**
     * Assign value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagBinary& operator =(const QVariant &v);

    /**
     * Tag multiplicity.
     * This method always returns 1 for binary tags.
     * \retur Tag's multiplicity.
     */
    int multiplicity() const;

    /**
     * Returns tag value as byte array.
     * \return Binary data.
     */
    QByteArray asByteArray() const;

    /**
     * Returns reference to tag's internal byte array.
     * \return Reference to tag's binary data.
     */
    QByteArray& data();

    /**
     * Returns pointer to a pixel data constant raw data.
     * \return Pointer to raw data.
     */
    const char* constData() const;

    /**
     * Assign tag's binary data.
     * \param byteArray Binary data to be assigned.
     */
    void setByteArray(const QByteArray &byteArray);

    /**
     * Returns this tag raw content size in bytes.
     * \param transferSyntax Transfer syntax to be used to encode the tag.
     * \return Content size in bytes.
     */
    DcmSize contentSize(const DcmTransferSyntax &transferSyntax) const;

private:

    QByteArray m_byteArray; ///< Binary data saved as byte array.
};

#endif // DCMTAGBINARY_H
