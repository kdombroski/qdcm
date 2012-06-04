#include "DcmGlobal.h"
#include "DcmTagDA.h"
#include "DcmTagTM.h"
#include "DcmModuleSOPCommon.h"

DcmModuleSOPCommon::DcmModuleSOPCommon()
    : DcmModule("SOPCommon")
{
    initializeTags();
    // Injecting QDCM version tag
    setTagValue("SoftwareVersions", QString("QDCM-%1").arg(VERSION));
}

DcmModuleSOPCommon::DcmModuleSOPCommon(const DcmModuleSOPCommon &module)
    : DcmModule(module)
{
}

DcmModuleSOPCommon& DcmModuleSOPCommon::operator =(const DcmModuleSOPCommon &module)
{
    if (this != &module) {
        DcmModule::operator =(module);
    }
    return *this;
}

DcmModule* DcmModuleSOPCommon::clone() const
{
    return new DcmModuleSOPCommon(*this);
}

QString DcmModuleSOPCommon::SOPClassUID() const
{
    return tagValue("SOPClassUID").toString();
}

void DcmModuleSOPCommon::setSOPClassUID(const QString &uid)
{
    Q_ASSERT(dcmIsValidUID(uid));
    setTagValue("SOPClassUID", uid);
}

QString DcmModuleSOPCommon::SOPInstanceUID() const
{
    return tagValue("SOPInstanceUID").toString();
}

void DcmModuleSOPCommon::setSOPInstanceUID(const QString &uid)
{
    Q_ASSERT(dcmIsValidUID(uid));
    setTagValue("SOPInstanceUID", uid);
}

QDate DcmModuleSOPCommon::instanceCreationDate() const
{
    DcmTag *tagPtr = tag("InstanceCreationDate");
    if (tagPtr) {
        DcmTagDA *tagDate = dynamic_cast<DcmTagDA*>(tagPtr);
        if (tagDate) {
            return tagDate->asDate();
        }
    }
    return QDate();
}

void DcmModuleSOPCommon::setInstanceCreationDate(const QDate &date)
{
    setTagValue("InstanceCreationDate", date);
}

QTime DcmModuleSOPCommon::instanceCreationTime() const
{
    DcmTag *tagPtr = tag("InstanceCreationTime");
    if (tagPtr) {
        DcmTagTM *tagTime = dynamic_cast<DcmTagTM*>(tagPtr);
        if (tagTime) {
            return tagTime->asTime();
        }
    }
    return QTime();
}

void DcmModuleSOPCommon::setInstanceCreationTime(const QTime &time)
{
    setTagValue("InstanceCreationTime", time);
}

QString DcmModuleSOPCommon::instanceCreatorUID() const
{
    return tagValue("InstanceCreatorUID").toString();
}

void DcmModuleSOPCommon::setInstanceCreatorUID(const QString &uid)
{
    Q_ASSERT(dcmIsValidUID(uid));
    setTagValue("InstanceCreatorUID", uid);
}

QString DcmModuleSOPCommon::softwareVersions() const
{
    return tagValue("softwareVersions").toString();
}

void DcmModuleSOPCommon::setSoftwareVersions(const QString &v)
{
    setTagValue("SoftwareVersions", v);
}

void DcmModuleSOPCommon::initializeTags()
{
    addSupportedTag("SOPClassUID", true);
    addSupportedTag("SOPInstanceUID", true);
    addSupportedTag("InstanceCreationDate", true);
    addSupportedTag("InstanceCreationTime", true);
    addSupportedTag("InstanceCreatorUID", false);
    addSupportedTag("SoftwareVersions", false);
}

