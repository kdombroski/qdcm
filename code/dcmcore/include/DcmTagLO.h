#ifndef DCMTAGLO_H
#define DCMTAGLO_H

#include "DcmCoreApi.h"
#include "DcmTagString.h"

/*! DICOM long string (LO) tag.
 *
 * LO tag, 64 symbols maximum.
 */
class DCM_CORE_API DcmTagLO: public DcmTagString
{
public:

    /**
     * Default constructor.
     */
    DcmTagLO();

    /**
     * Construct LO tag.
     * \param tagKey Tag key.
     */
    DcmTagLO(const DcmTagKey &tagKey);

    /**
     * Copy constructor.
     * \param tag Tag to be copied.
     */
    DcmTagLO(const DcmTagLO &tag);

    /**
     * Assignment operator.
     * \param tag Tag to be assigned.
     * \return This tag.
     */
    DcmTagLO& operator =(const DcmTagLO &tag);

    /**
     * Clone this tag.
     * \return Pointer to cloned tag.
     */
    DcmTag* clone() const;

    /**
     * Destructor.
     */
    ~DcmTagLO();

    /**
     * Assign tag value.
     * \param v Value to be set.
     * \return This tag.
     */
    DcmTagLO& operator =(const QVariant &v);

};

#endif // DCMTAGLO_H
