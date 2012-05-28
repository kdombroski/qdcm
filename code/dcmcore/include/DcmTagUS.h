#ifndef DCMTAGUS_H
#define DCMTAGUS_H

#include "DcmCoreApi.h"
#include "DcmTag.h"

/*! DICOM Unsigned Short (US) tag.
 *
 * Unsigned binary integer 16 bits long.
 */
class DCM_CORE_API DcmTagUS: public DcmTag
{
public:

    /**
     * Default constructor.
     */
    DcmTagUS();

    /**
     * Construct US tag.
     * \param tagKey Tag key.
     */
    DcmTagUS(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagUS(const DcmTagUS &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagUS& operator =(const DcmTagUS &tag);

    /**
     * Clone this tag.
     * \return Pointer to this tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagUS();

    /**
     * Returns tag's first value.
     * \return Tag's value.
     */
    QVariant value() const;

    /**
     * Returns tag's values.
     * \return Tag's values.
     */
    QVariantList values() const;

    /**
     * Assign tag value.
     * This method takes integer value.
     * \param v Values to be assigned.
     */
    void setValue(const QVariant &v);

    /**
     * Append value.
     * This method takes integer value.
     * \param v Values to be added.
     */
    void appendValue(const QVariant &v);

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagUS& operator =(const QVariant &v);

    /**
     * Returns multiplicity of this tag.
     * \return Tag's multiplicity.
     */
    int multiplicity() const;

    /**
     * Returns tag's value as unsigned short.
     * If tag is empty, zero is returned.
     * \return Tag's value.
     */
    DcmUnsignedShort asUnsignedShort() const;

    /**
     * Returns list of tag's values.
     * \return List of tag's values.
     */
    QList<DcmUnsignedShort> asUnsignedShortList() const;

    /**
     * Assign tag value.
     * \param v Value to be assigned.
     */
    void setUnsignedShort(DcmUnsignedShort v);

    /**
     * Append tag value.
     * \param v Value to be added.
     */
    void appendUnsignedShort(DcmUnsignedShort v);

    /**
     * Returns tag's raw content size in bytes.
     * This will return 2 * multiplicity (US tag single value takes 2 bytes).
     * \param transferSyntax Transfer syntax to encode the tag.
     * \return Tag's content size in bytes.
     */
    DcmSize contentSize(const DcmTransferSyntax &transferSyntax) const;

private:

    QList<DcmUnsignedShort> m_values;   ///< List of values.
};

#endif // DCMTAGUS_H
