#ifndef DCMTAGSH_H
#define DCMTAGSH_H

#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM short string tag.
 *
 * This class represents short string tag (16 symbols maximum).
 */
class DCM_CORE_API DcmTagSH: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagSH();

    /**
     * Construct SH tag.
     * \param tagKey Tag key.
     */
    DcmTagSH(const DcmTagKey &tagKey);

    /**
     * Copy constrcutor.
     * \param tag Tag to be copied.
     */
    DcmTagSH(const DcmTagSH &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagSH& operator =(const DcmTagSH &tag);

    /**
     * Clone this tag.
     * \return Cloned tag.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagSH();

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagSH& operator =(const QVariant &v);
};

#endif // DCMTAGSH_H
