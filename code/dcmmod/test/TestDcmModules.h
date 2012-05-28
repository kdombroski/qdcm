#ifndef TESTDCMMODULES_H
#define TESTDCMMODULES_H

#include <QtTest/QtTest>
#include "DcmDataset.h"
#include "DcmModuleSOPCommon.h"
#include "DcmModulePatient.h"
#include "DcmModuleStudy.h"

class TestDcmModules: public QObject
{
    Q_OBJECT

private slots:

    void initTestCase()
    {}

    void testDcmModuleSOPCommon()
    {
        DcmModuleSOPCommon mod;

        QVERIFY(!mod.isValid());

        mod.setSOPClassUID("1.2.3.4.5");
        mod.setSOPInstanceUID("2.3.4.5.6");
        mod.setInstanceCreatorUID("3.4.5.6.7");
        mod.setInstanceCreationDate(QDate(2010, 03, 15));
        mod.setInstanceCreationTime(QTime(13, 45, 16, 325));

        QVERIFY(mod.isValid());

        mod.setSoftwareVersion("QDCM-1.0");

        DcmDataset dataset;
        dataset.attachModule(mod);

        QVERIFY(dataset.findTag("SOPClassUID"));
        QVERIFY(dataset.findTag("SOPInstanceUID"));
        QVERIFY(dataset.findTag("InstanceCreatorUID"));
        QVERIFY(dataset.findTag("InstanceCreationDate"));
        QVERIFY(dataset.findTag("InstanceCreationTime"));
        QVERIFY(dataset.findTag("SoftwareVersion"));

        DcmModuleSOPCommon mod2;
        mod2.fetchFromDataset(dataset);

        QVERIFY(mod2.isValid());
        QCOMPARE(mod2.SOPClassUID(), QString("1.2.3.4.5"));
        QCOMPARE(mod2.SOPInstanceUID(), QString("2.3.4.5.6"));
        QCOMPARE(mod2.instanceCreatorUID(), QString("3.4.5.6.7"));
        QCOMPARE(mod2.instanceCreationDate(), QDate(2010, 03, 15));
        QCOMPARE(mod2.instanceCreationTime(), QTime(13, 45, 16, 325));
        QCOMPARE(mod2.softwareVersion(), QString("QDCM-1.0"));
    }

    void testDcmModulePatient()
    {
        DcmModulePatient mod;

        QVERIFY(!mod.isValid());

        mod.setPatientId("PAT1234");
        mod.setPatientName("Brown^John");
        QVERIFY(mod.isValid());

        mod.setPatientBirthDate(QDate(1976, 12, 4));
        mod.setPatientBirthTime(QTime(5, 55, 35, 135));
        mod.setPatientSex("M");

        DcmDataset dataset;
        dataset.attachModule(mod);

        QVERIFY(dataset.findTag("PatientName"));
        QVERIFY(dataset.findTag("PatientID"));
        QVERIFY(dataset.findTag("PatientBirthDate"));
        QVERIFY(dataset.findTag("PatientBirthTime"));
        QVERIFY(dataset.findTag("PatientSex"));

        DcmModulePatient mod2;
        mod2.fetchFromDataset(dataset);

        QVERIFY(mod2.isValid());
        QCOMPARE(mod2.patientName(), QString("Brown^John"));
        QCOMPARE(mod2.patientId(), QString("PAT1234"));
        QCOMPARE(mod2.patientBirthDate(), QDate(1976, 12, 4));
        QCOMPARE(mod2.patientBirthTime(), QTime(5, 55, 35, 135));
        QCOMPARE(mod2.patientSex(), QString("M"));
    }

    void testDcmModuleStudy()
    {
        DcmModuleStudy mod;

        QVERIFY(!mod.isValid());

        mod.setStudyInstanceUID("1.2.3.4.5.6");
        mod.setStudyDate(QDate(2011, 3, 4));
        mod.setStudyTime(QTime(7, 15, 38, 17));
        QVERIFY(mod.isValid());
        mod.setStudyId("SID");
        mod.setReferringPhysicianName("Who^Doctor");
        mod.setStudyDescription("Study description.");

        DcmDataset dataset;
        dataset.attachModule(mod);

        QVERIFY(dataset.findTag("StudyInstanceUID"));
        QVERIFY(dataset.findTag("StudyDate"));
        QVERIFY(dataset.findTag("StudyTime"));
        QVERIFY(dataset.findTag("StudyID"));
        QVERIFY(dataset.findTag("ReferringPhysicianName"));
        QVERIFY(dataset.findTag("StudyDescription"));

        DcmModuleStudy mod2;
        mod2.fetchFromDataset(dataset);

        QVERIFY(mod2.isValid());
        QCOMPARE(mod2.studyInstanceUID(), QString("1.2.3.4.5.6"));
        QCOMPARE(mod2.studyDate(), QDate(2011, 3, 4));
        QCOMPARE(mod2.studyTime(), QTime(7, 15, 38, 17));
        QCOMPARE(mod2.studyId(), QString("SID"));
        QCOMPARE(mod2.referringPhysicianName(), QString("Who^Doctor"));
        QCOMPARE(mod2.studyDescription(), QString("Study description."));
    }

    void cleanupTestCase()
    {}
};

#endif // TESTDCMMODULES_H
