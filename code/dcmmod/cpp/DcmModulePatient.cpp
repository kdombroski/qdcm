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
    addSupportedTag("PatientName", DcmModule::TagType_2);
    addSupportedTag("PatientID", DcmModule::TagType_2);
    addSupportedTag("PatientBirthDate", DcmModule::TagType_2);
    addSupportedTag("PatientSex", DcmModule::TagType_2);
    addSupportedTag(DcmTagKey(0x0008, 0x1120), DcmModule::TagType_3);   // Referenced Patient Sequence
    addSupportedTag("PatientBirthTime", DcmModule::TagType_3);
    addSupportedTag(DcmTagKey(0x0010, 0x1000), DcmModule::TagType_3);   // Other Patient IDs
    addSupportedTag(DcmTagKey(0x0010, 0x1002), DcmModule::TagType_3);   // Other Patient IDs Sequence
    addSupportedTag(DcmTagKey(0x0010, 0x1001), DcmModule::TagType_3);   // Other Patient Names
    addSupportedTag(DcmTagKey(0x0010, 0x2160), DcmModule::TagType_3);   // Ethnic group or race
    addSupportedTag(DcmTagKey(0x0010, 0x4000), DcmModule::TagType_3);   // Patient comments
    addSupportedTag(DcmTagKey(0x0010, 0x2201), DcmModule::TagType_1C);  // Patient Species
    addSupportedTag(DcmTagKey(0x0010, 0x2202), DcmModule::TagType_1C);  // Patient Species Code Sequence
    addSupportedTag(DcmTagKey(0x0010, 0x2292), DcmModule::TagType_2C);  // Patient Breed Description
    addSupportedTag(DcmTagKey(0x0010, 0x2293), DcmModule::TagType_2C);  // Patient Breed Code Sequence
    addSupportedTag(DcmTagKey(0x0010, 0x2294), DcmModule::TagType_2C);  // Breed registration sequence
    addSupportedTag(DcmTagKey(0x0010, 0x2297), DcmModule::TagType_2C);  // Responsible person
    addSupportedTag(DcmTagKey(0x0010, 0x2298), DcmModule::TagType_1C);  // Responsible Person Role
    addSupportedTag(DcmTagKey(0x0010, 0x2299), DcmModule::TagType_2C);  // Responsible Organization
    addSupportedTag(DcmTagKey(0x0012, 0x0062), DcmModule::TagType_3);   // Patient Identity Removed ('YES' or 'NO')
    addSupportedTag(DcmTagKey(0x0012, 0x0063), DcmModule::TagType_1C);  // Deidentification Method
    addSupportedTag(DcmTagKey(0x0012, 0x0064), DcmModule::TagType_1C);  // Deidentification Method Code Sequence
}
