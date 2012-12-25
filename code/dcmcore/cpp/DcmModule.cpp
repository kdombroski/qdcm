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

#include <QDebug>
#include "DcmDictionary.h"
#include "DcmDataset.h"
#include "DcmModule.h"

DcmModule::DcmModule(const QString &name)
    : m_name(name),
      m_mandatoryTagKeys(),
      m_optionalTagKeys(),
      m_tagsList()
{
}

DcmModule::DcmModule(const DcmModule &module)
    : m_name(module.m_name),
      m_mandatoryTagKeys(module.m_mandatoryTagKeys),
      m_optionalTagKeys(module.m_optionalTagKeys),
      m_tagsList(module.m_tagsList)
{
}

DcmModule& DcmModule::operator =(const DcmModule &module)
{
    if (this != &module) {
        m_name = module.m_name;
        m_mandatoryTagKeys = module.m_mandatoryTagKeys;
        m_optionalTagKeys = module.m_optionalTagKeys;
        m_tagsList = module.m_tagsList;
    }
    return *this;
}

DcmModule* DcmModule::clone() const
{
    return new DcmModule(*this);
}

DcmModule::~DcmModule()
{
}

QString DcmModule::name() const
{
    return m_name;
}

QList<DcmTagKey> DcmModule::mandatoryTagKeys() const
{
    return m_mandatoryTagKeys;
}

QList<DcmTagKey> DcmModule::optionalTagKeys() const
{
    return m_optionalTagKeys;
}

void DcmModule::fetchFromDataset(const DcmDataset &dataset)
{
    fetchTags(dataset, m_mandatoryTagKeys);
    fetchTags(dataset, m_optionalTagKeys);
}

bool DcmModule::isValid() const
{
    bool valid = true;
    foreach (DcmTagKey tagKey, m_mandatoryTagKeys) {
        DcmTag *tag = m_tagsList.findFirst(tagKey);
        if (!tag) {
            valid = false;
            break;
        }
    }

    return valid;
}

DcmTag* DcmModule::tag(const DcmTagKey &tagKey) const
{
    if (m_mandatoryTagKeys.contains(tagKey)
            || m_optionalTagKeys.contains(tagKey)) {

        return m_tagsList.findFirst(tagKey);
    }

    // Tag is not handled by this module
    return 0;
}

DcmTag* DcmModule::tag(const QString &name) const
{
    DcmTagDescription desc = DcmDictionary::getInstancePtr()->findByName(name);
    if (desc.isValid()) {
        return tag(desc.tagKey());
    }
    return 0;
}

QVariant DcmModule::tagValue(const DcmTagKey &tagKey) const
{
    DcmTag *tagPtr = tag(tagKey);
    if (tagPtr) {
        return tagPtr->value();
    }
    return QVariant();
}

QVariant DcmModule::tagValue(const QString &tagName) const
{
    DcmTag *tagPtr = tag(tagName);
    if (tagPtr) {
        return tagPtr->value();
    }
    return QVariant();
}

QVariantList DcmModule::tagValues(const DcmTagKey &tagKey) const
{
    DcmTag *tagPtr = tag(tagKey);
    if (tagPtr) {
        return tagPtr->values();
    }
    return QVariantList();
}

QVariantList DcmModule::tagValues(const QString &tagName) const
{
    DcmTag *tagPtr = tag(tagName);
    if (tagPtr) {
        return tagPtr->values();
    }
    return QVariantList();
}

void DcmModule::setTagValue(const DcmTagKey &tagKey, const QVariant &value)
{
    if ((!m_mandatoryTagKeys.contains(tagKey)) && (!m_optionalTagKeys.contains(tagKey))) {
        qWarning() << "Tag " << tagKey.toString() << "is not a part of the module" << name();
        return;
    }

    DcmTag *tagPtr = DcmTag::create(tagKey);
    tagPtr->setValue(value);
    m_tagsList.insertOrReplaceAndRetain(tagPtr);
}

void DcmModule::setTagValues(const DcmTagKey &tagKey, const QVariantList &values)
{
    if ((!m_mandatoryTagKeys.contains(tagKey)) && (!m_optionalTagKeys.contains(tagKey))) {
        qWarning() << "Tag " << tagKey.toString() << "is not a part of the module.";
        return;
    }

    DcmTag *tagPtr = DcmTag::create(tagKey);
    foreach (QVariant v, values) {
        tagPtr->appendValue(v);
    }
    m_tagsList.insertOrReplaceAndRetain(tagPtr);
}

void DcmModule::setTagValue(const QString &tagName, const QVariant &value)
{
    DcmTagDescription desc = DcmDictionary::getInstancePtr()->findByName(tagName);
    if (desc.isValid()) {
        setTagValue(desc.tagKey(), value);
    } else {
        qWarning() << "Tag" << tagName << "is unknown";
    }
}

void DcmModule::setTagValues(const QString &tagName, const QVariantList &values)
{
    DcmTagDescription desc = DcmDictionary::getInstancePtr()->findByName(tagName);
    if (desc.isValid()) {
        if (!desc.isValidMultiplicity(values.count())) {
            qWarning() << "Tag" << tagName << desc.tagKey().toString()
                       << "multiplicity" << values.count() << "is invalid.";
        }
        setTagValues(desc.tagKey(), values);
    } else {
        qWarning() << "Tag" << tagName << "is unknown";
    }
}

DcmTagList DcmModule::tagList() const
{
    return m_tagsList;
}

void DcmModule::addSupportedTag(const DcmTagKey &tagKey, bool mandatory)
{
    if (mandatory) {
        if (!m_mandatoryTagKeys.contains(tagKey)) {
            m_mandatoryTagKeys.append(tagKey);
        }
    } else {
        if (!m_optionalTagKeys.contains(tagKey)) {
            m_optionalTagKeys.append(tagKey);
        }
    }
}

void DcmModule::addSupportedTag(const QString &tagName, bool mandatory)
{
    DcmTagDescription desc = DcmDictionary::getInstancePtr()->findByName(tagName);
    if (desc.isValid()) {
        addSupportedTag(desc.tagKey(), mandatory);
    }
}

void DcmModule::fetchTags(const DcmDataset &dataset, const QList<DcmTagKey> &tagKeys)
{
    foreach (DcmTagKey tagKey, tagKeys) {
        DcmTag *tagPtr = dataset.findTag(tagKey);
        if (tagPtr) {
            m_tagsList.insertOrReplace(*tagPtr);
        }
    }
}
