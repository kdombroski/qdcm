#include <QDebug>
#include "DcmTagPixelData.h"
#include "DcmImage.h"

DcmImage::DcmImage(int width, int height, int frames, int bitsAllocated, int bitsStored, int highBit, int samplesPerPixel, const DcmPhotometricInterpretation &pi)
{
    Q_ASSERT(width > 0);
    Q_ASSERT(height > 0);
    Q_ASSERT(frames > 0);
    Q_ASSERT((bitsAllocated == 8)
             || (bitsAllocated == 16)
             || (bitsAllocated == 32));
    Q_ASSERT((bitsStored > 0)
             &&(bitsStored <= bitsAllocated));
    Q_ASSERT(highBit < bitsAllocated);
    Q_ASSERT(bitsStored <= highBit + 1);
    Q_ASSERT(samplesPerPixel > 0);

    m_datasetPtr = new DcmDataset();
    m_datasetPtr->setTagValue("Columns", width);
    m_datasetPtr->setTagValue("Rows", height);
    m_datasetPtr->setTagValue("Frames", frames);
    m_datasetPtr->setTagValue("BitsAllocated", bitsAllocated);
    m_datasetPtr->setTagValue("BitsStored", bitsStored);
    m_datasetPtr->setTagValue("HighBit", highBit);
    m_datasetPtr->setTagValue("SamplesPerPixel", samplesPerPixel);
    m_datasetPtr->setTagValue("PhotometricInterpretation", pi.toString());

    allocatePixelData();
}

DcmImage::DcmImage(const DcmDataset *datasetPtr)
{
    Q_ASSERT(datasetPtr);
    if (!datasetPtr) {
        return;
    }

    m_datasetPtr = new DcmDataset(*datasetPtr);
}

DcmImage::DcmImage(const DcmImage &image)
{
    m_datasetPtr = new DcmDataset(*image.m_datasetPtr);
}

DcmImage& DcmImage::operator =(const DcmImage &image)
{
    if (this != &image) {
        delete m_datasetPtr;
    }
    return *this;
}

DcmImage::~DcmImage()
{
    delete m_datasetPtr;
}

int DcmImage::width() const
{
    return m_datasetPtr->tagValue("Columns").toInt();
}

int DcmImage::height() const
{
    return m_datasetPtr->tagValue("Rows").toInt();
}

int DcmImage::frames() const
{
    QVariant v = m_datasetPtr->tagValue("Frames");
    if (v.isValid()) {
        return v.toInt();
    }
    return 1;
}

int DcmImage::bitsAllocated() const
{
    return m_datasetPtr->tagValue("BitsAllocated").toInt();
}

int DcmImage::bitsStored() const
{
    return m_datasetPtr->tagValue("BitsStored").toInt();
}

int DcmImage::highBit() const
{
    return m_datasetPtr->tagValue("HighBit").toInt();
}

int DcmImage::samplesPerPixel() const
{
    return m_datasetPtr->tagValue("SamplesPerPixel").toInt();
}

DcmPhotometricInterpretation DcmImage::photometricInterpretation() const
{
    return DcmPhotometricInterpretation::bySignature(m_datasetPtr->tagValue("PhotometricInterpretation").toString());
}

DcmDataset* DcmImage::dataset()
{
    return m_datasetPtr;
}

void DcmImage::allocatePixelData()
{
    int bytesToAllocate = width() * height() * frames() * bitsAllocated() * samplesPerPixel() / 8;
    QByteArray ba = QByteArray(bytesToAllocate, 0);
    // We always allocate pixel data as OW value representation.
    DcmTagPixelData tagPixelData(DcmTagPixelData::Format_Native, DcmVr::OW);
    tagPixelData.setByteArray(ba);
    m_datasetPtr->insert(tagPixelData);
}
