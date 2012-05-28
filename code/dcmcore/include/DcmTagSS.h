#ifndef DCMTAGSS_H
#define DCMTAGSS_H

#include "DcmCoreApi.h"
#include "DcmTag.h"

/*! DICOM Signed Short (SS) tag.
 *
 * Signed binary integer 16 bits long.
 */
class DCM_CORE_API DcmTagSS: public DcmTag
{
public:

    /**
     * Default constructor.
     */
    DcmTagSS();

    /**
     * Construct SS tag.
     * \param tagKey Tag key.
     */
    DcmTagSS(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagSS(const DcmTagSS &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagSS& operator =(const DcmTagSS &tag);

    /**
     * Clone this tag.
     * \return Pointer to this tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagSS();

    /**
     * Return tag's first value.
     * \return Tag's value.
     */
    QVariant value() const;

    /**
     * Return tag's values.
     * \return Tag's values.
     */
    QVariantList values() const;

    /**
     * Assign tag value.
     * This method takes integer value.
     * \param v Value to be assigned.
     */
    void setValue(const QVariant &v);

    /**
     * Append value.
     * This method takes integer value.
     * \param v Value to be added.
     */
    void appendValue(const QVariant &v);

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagSS& operator =(const QVariant &v);

    /**
     * Returns multiplicity of this tag.
     * \return Tag's multiplicity.
     */
    int multiplicity() const;

    /**
     * Return tag's value as signed short.
     * If tag is empty, zero is returned.
     * \return Tag's value.
     */
    DcmSignedShort asSignedShort() const;

    /**
     * Returns list of tag's values.
     * \return List of tag's values.
     */
    QList<DcmSignedShort> asSignedShortList() const;

    /**
     * Assign tag value.
     * \param v Value to be assigned.
     */
    void setSignedShort(DcmSignedShort v);

    /**
     * Append tag value.
     * \param v Value to be added.
     */
    void appendSignedShort(DcmSignedShort v);

    /**
     * Returns tag's raw content size in bytes.
     * This will give 2 * multiplicity (SS tag single value takes 2 bytes).
     * \param transferSyntax Transfer syntax to encode the tag.
     * \return Tag's content size in bytes.
     */
    DcmSize contentSize(const DcmTransferSyntax &transferSyntax) const;

private:

    QList<DcmSignedShort> m_values; ///< List of values.
};

#endif // DCMTAGSS_H
