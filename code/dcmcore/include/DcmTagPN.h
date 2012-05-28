#ifndef DCMTAGPN_H
#define DCMTAGPN_H

#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM Patient Name (PN) tag.
 *
 * This tag holds a patient name.
 * Patient's last and first names are separated
 * by '^' character.
 */
class DCM_CORE_API DcmTagPN: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagPN();

    /**
     * Construct PN tag.
     * \param tagKey Tag key.
     */
    DcmTagPN(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagPN(const DcmTagPN &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagPN& operator =(const DcmTagPN &tag);

    /**
     * Clone this tag.
     * \return Pinter to the tag's clone.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagPN();

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagPN& operator =(const QVariant &v);
};

#endif // DCMTAGPN_H
