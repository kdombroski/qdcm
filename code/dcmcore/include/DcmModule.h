/* This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#ifndef DCMMODULE_H
#define DCMMODULE_H

#include <QList>
#include "DcmCoreApi.h"
#include "DcmTagKey.h"
#include "DcmTagList.h"

class DcmDataset;

/*! DICOM module.
 * This is a base class for DICOM modules.
 * A module contains a list of tags grouped.
 * All tags are split into two categories: mandatory and optional.
 * Module is valid only when all mandatory tags are set.
 */
class DCM_CORE_API DcmModule
{
public:

    /**
     * Construct an empty module.
     */
    DcmModule(const QString &name = QString());

    /**
     * Copy constructor.
     * \param module Module to be copied.
     */
    DcmModule(const DcmModule &module);

    /**
     * Assignment operator.
     * \param module Module to be assigned.
     * \return This module.
     */
    DcmModule& operator =(const DcmModule &module);

    /**
     * Clone this module.
     * \return Pointer to module's clone.
     */
    DcmModule* clone() const;

    /**
     * Destructor.
     */
    virtual ~DcmModule();

    /**
     * Returns module name.
     * \return Name of this module.
     */
    QString name() const;

    /**
     * Returns a reference to the list of mandatory tag keys.
     * \return List of mandatry tag keys.
     */
    QList<DcmTagKey> mandatoryTagKeys() const;

    /**
     * Returns a reference to the list of optional tag keys.
     * \return List of optional tag keys.
     */
    QList<DcmTagKey> optionalTagKeys() const;

    /**
     * Fetch tags from the dataset.
     * This method fetches mandatory and optional keys from
     * the dataset to store them in this module.
     * \param datasetPtr Pointer to the dataset.
     */
    void fetchFromDataset(const DcmDataset &dataset);

    /**
     * Tells whether the module is valid.
     * A valid module must have all its mandatory tags.
     * \return True is all mandatory tags are present.
     */
    bool isValid() const;

    /**
     * Returns tag by the key.
     * Null is returned if not found.
     * \param tagKey Tag key.
     * \return Pointer to a tag.
     */
    DcmTag* tag(const DcmTagKey &tagKey) const;

    /**
     * Returns tag by the name.
     * Null is returned if not found.
     * \param name Tag name.
     * \return Pointer to a tag.
     */
    DcmTag* tag(const QString &name) const;

    /**
     * Returns tag value.
     * \param tagKey Tag key.
     * \return Tag value.
     */
    QVariant tagValue(const DcmTagKey &tagKey) const;

    /**
     * Returns tag values.
     * \param tagKeys Tag key.
     * \return List of tag values.
     */
    QVariantList tagValues(const DcmTagKey &tagKey) const;

    /**
     * Returns tag value by tag's name.
     * Returns empty value if tag not found.
     * \param tagName Tag name.
     * \return Tag value.
     */
    QVariant tagValue(const QString &tagName) const;

    /**
     * Returns tag values.
     * \param tagName Tag name.
     * \return Tag values.
     */
    QVariantList tagValues(const QString &tagName) const;

    /**
     * Assign module tag value.
     * \param tagKey Tag key.
     * \param value Value to be assigned.
     */
    void setTagValue(const DcmTagKey &tagKey, const QVariant &value);

    /**
     * Assign tag values.
     * @param tagKey Tag key.
     * @param values Values to be assigned.
     */
    void setTagValues(const DcmTagKey &tagKey, const QVariantList &values);

    /**
     * Assign module tag value.
     * \param tagName Tag name.
     * \param value Value to be assigned.
     */
    void setTagValue(const QString &tagName, const QVariant &value);

    /**
     * Assign module tag values.
     * @param tagName Tag name.
     * @param values Values to be assigned.
     */
    void setTagValues(const QString &tagName, const QVariantList &values);

    /**
     * Reutns tags list of this module.
     * \return List of tags.
     */
    DcmTagList tagList() const;

protected:

    /**
     * Add tag key to the list of supported tags.
     * \param tagKey Tag key to be added.
     * \param mandatory Whether this tag key is mandatory.
     */
    void addSupportedTag(const DcmTagKey &tagKey, bool mandatory = true);

    /**
     * Add tag key to the list of supported tags.
     * \param tagName Tag name.
     * \param mandatory Whether this tag is mandatory.
     */
    void addSupportedTag(const QString &tagName, bool mandatory = true);

private:

    /**
     * Fetch tags from dataset.
     * \param datasetPtr Pointer to a dataset.
     * \param tagKeys List of tag keys to be fetched.
     */
    void fetchTags(const DcmDataset &datasetPtr, const QList<DcmTagKey> &tagKeys);

    QString m_name;     ///< Module name.
    QList<DcmTagKey> m_mandatoryTagKeys;    ///< List of mandatory tag keys.
    QList<DcmTagKey> m_optionalTagKeys;     ///< List of optional tag keys.

    DcmTagList m_tagsList;  ///< List of tags set in the module.

};

#endif // DCMMODULE_H
