#include "DcmTagDA.h"
#include "DcmTagTM.h"
#include "DcmModulePatient.h"

DcmModulePatient::DcmModulePatient()
    : DcmModule("Patient")
{
    initializeTags();
}

DcmModulePatient::DcmModulePatient(const DcmModulePatient &module)
    : DcmModule(module)
{
}

DcmModulePatient& DcmModulePatient::operator =(const DcmModulePatient &module)
{
    if (this != &module) {
        DcmModule::operator =(module);
    }
    return *this;
}

DcmModule* DcmModulePatient::clone() const
{
    return new DcmModulePatient(*this);
}

QString DcmModulePatient::patientName() const
{
    return tagValue("PatientName").toString();
}

void DcmModulePatient::setPatientName(const QString &name)
{
    setTagValue("PatientName", name);
}

QString DcmModulePatient::patientId() const
{
    return tagValue("PatientID").toString();
}

void DcmModulePatient::setPatientId(const QString &id)
{
    setTagValue("PatientID", id);
}

QDate DcmModulePatient::patientBirthDate() const
{
    DcmTag *tagPtr = tag("PatientBirthDate");
    if (tagPtr) {
        DcmTagDA *tagDate = dynamic_cast<DcmTagDA*>(tagPtr);
        if (tagDate) {
            return tagDate->asDate();
        }
    }
    return QDate();
}

void DcmModulePatient::setPatientBirthDate(const QDate &date)
{
    setTagValue("PatientBirthDate", date);
}

QTime DcmModulePatient::patientBirthTime() const
{
    DcmTag *tagPtr = tag("PatientBirthTime");
    if (tagPtr) {
        DcmTagTM *tagTime = dynamic_cast<DcmTagTM*>(tagPtr);
        if (tagTime) {
            return tagTime->asTime();
        }
    }
    return QTime();
}

void DcmModulePatient::setPatientBirthTime(const QTime &time)
{
    setTagValue("PatientBirthTime", time);
}

QString DcmModulePatient::patientSex() const
{
    return tagValue("PatientSex").toString();
}

void DcmModulePatient::setPatientSex(const QString &s)
{
    setTagValue("PatientSex", s);
}

void DcmModulePatient::initializeTags()
{
    addSupportedTag("PatientName", true);
    addSupportedTag("PatientID", true);
    addSupportedTag("PatientBirthDate", false);
    addSupportedTag("PatientBirthTime", false);
    addSupportedTag("PatientSex", false);
}
