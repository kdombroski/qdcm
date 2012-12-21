#include <QDebug>
#include "DcmTagPixelData.h"
#include "DcmTagDS.h"
#include "DcmImage.h"

DcmImage::DcmImage(int width,
                   int height,
                   int frames,
                   int bitsAllocated,
                   int bitsStored,
                   int highBit,
                   int samplesPerPixel,
                   const DcmPhotometricInterpretation &pi)
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

    m_tagPixelDataPtr = dynamic_cast<DcmTagPixelData*>(m_datasetPtr->findTag(DcmTagKey::PixelData));
}

DcmImage::DcmImage(const DcmDataset *datasetPtr)
{
    Q_ASSERT(datasetPtr);
    if (!datasetPtr) {
        return;
    }

    m_datasetPtr = new DcmDataset(*datasetPtr);
    DcmTag *tagPtr = m_datasetPtr->findTag(DcmTagKey::PixelData);
    if (tagPtr) {
        m_tagPixelDataPtr = dynamic_cast<DcmTagPixelData*>(tagPtr);
    } else {
        // The dataset does not contain pixel data
        m_tagPixelDataPtr = 0;
    }
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

double DcmImage::rescaleIntercept() const
{
    QVariant v = m_datasetPtr->tagValue("RescaleIntercept");
    if (v.isValid()) {
        bool ok = true;
        double d = v.toDouble(&ok);
        if (ok) {
            return d;
        }
    }

    return 0.0;
}

void DcmImage::setRescaleIntercept(double ri)
{
    m_datasetPtr->setTagValue("RescaleIntercept", QVariant(ri));
}

double DcmImage::rescaleSlope() const
{
    QVariant v = m_datasetPtr->tagValue("RescaleSlope");
    if (v.isValid()) {
        bool ok = true;
        double d = v.toDouble(&ok);
        if (ok) {
            return d;
        }
    }

    return 1.0;
}

void DcmImage::setRescaleSlope(double rs)
{
    m_datasetPtr->setTagValue("RescaleSlope", QVariant(rs));
}

double DcmImage::windowCenter() const
{
    DcmTag *tag = m_datasetPtr->findTag("WindowCenter");
    if (tag) {
        DcmTagDS *tagDS = dynamic_cast<DcmTagDS *>(tag);
        if (tagDS) {
            return tagDS->asDouble();
        }
    }

    return ((double)(1 << bitsStored())) / 2;
}

void DcmImage::setWindowCenter(double c)
{
    m_datasetPtr->setTagValue("WindowCenter", QVariant(c));
}

double DcmImage::windowWidth() const
{
    DcmTag *tag = m_datasetPtr->findTag("WindowWidth");
    if (tag) {
        DcmTagDS *tagDS = dynamic_cast<DcmTagDS *>(tag);
        if (tagDS) {
            return tagDS->asDouble();
        }
    }

    return (double)(1 << bitsStored());
}

QString DcmImage::rescaleTypeString() const
{
    return m_datasetPtr->tagValue("RescaleType").toString().trimmed();
}

void DcmImage::setRescaleTypeString(const QString &rt)
{
    m_datasetPtr->setTagValue("RescaleType", QVariant(rt.trimmed()));
}

DcmDataset* DcmImage::dataset() const
{
    return m_datasetPtr;
}

DcmTagPixelData* DcmImage::tagPixelData() const
{
    return m_tagPixelDataPtr;
}

bool DcmImage::isValid() const
{
    // Check we have a pixel data present
    if (!m_tagPixelDataPtr) {
        return false;
    }

    // Check raw pixel data size is correct
    DcmSize size = width() * height() * frames() * bitsAllocated() * samplesPerPixel() / 8;
    if (size & 1) {
        size += 1;  // Correct for even size
    }

    // Check pixel data size for native (not compressed) image
    if (m_tagPixelDataPtr->isNative()) {
        // Transfer syntax does not affect pixel data tag content size (as it is a binary tag).
        if (size != m_tagPixelDataPtr->contentSize(DcmTransferSyntax::ImplicitLittleEndian)) {
            return false;
        }
    }

    return true;
}

quint32 DcmImage::pixelByteArrayIndex(int x, int y, int frame) const
{
    quint32 adj = bitsAllocated() * samplesPerPixel() / 8;
    quint32 idx = (x + y * width()) * adj;

    idx += frame * width() * height() * adj;
    return idx;
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
