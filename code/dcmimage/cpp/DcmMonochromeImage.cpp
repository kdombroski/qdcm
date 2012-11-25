#include "DcmTagPixelData.h"
#include "DcmMonochromeImage.h"

DcmMonochromeImage::DcmMonochromeImage(int width,
                                       int height,
                                       int frames,
                                       int bitsAllocated,
                                       int bitsStored,
                                       int highBit,
                                       const DcmPhotometricInterpretation &pi)
    : DcmImage(width, height, frames, bitsAllocated, bitsStored, highBit, 1 /* samples per pixel */, pi)
{
}

DcmMonochromeImage::DcmMonochromeImage(const DcmDataset *datasetPtr)
    : DcmImage(datasetPtr)
{
}

DcmMonochromeImage::DcmMonochromeImage(const DcmMonochromeImage &monoImage)
    : DcmImage(monoImage)
{
}

DcmMonochromeImage& DcmMonochromeImage::operator =(const DcmMonochromeImage &monoImage)
{
    if (this != &monoImage) {
        DcmImage::operator =(monoImage);
    }
    return *this;
}

DcmMonochromeImage::~DcmMonochromeImage()
{
}

bool DcmMonochromeImage::isValid() const
{
    if (!DcmImage::isValid()) {
        return false;
    }

    // Check photometric interpretation
    DcmPhotometricInterpretation pi = photometricInterpretation();
    return (pi == DcmPhotometricInterpretation::Monochrome1) || (pi == DcmPhotometricInterpretation::Monochrome2);
}

DcmUnsignedShort DcmMonochromeImage::rawPixel(int x, int y, int frame) const
{
    Q_ASSERT(x >= 0 && x < width());
    Q_ASSERT(y >= 0 && y < height());
    Q_ASSERT(frame >= 0 && frame < frames());
    Q_ASSERT(isValid());

    DcmTagPixelData *tagPixelDataPtr = tagPixelData();
    Q_ASSERT(tagPixelDataPtr);

    quint32 idx = pixelByteArrayIndex(x, y, frame);
    const char *rawBytePtr = &(tagPixelDataPtr->constData()[idx]);

    DcmUnsignedShort pixel = 0;

    if (bitsAllocated() > 8) {
        // One 16-bits word per pixel
        pixel = *((const DcmUnsignedShort*)rawBytePtr);
    } else {
        // One byte per pixel
        pixel = (DcmUnsignedShort)*((const unsigned char*)rawBytePtr);
    }

    return pixel;
}

void DcmMonochromeImage::setRawPixel(DcmUnsignedShort p, int x, int y, int frame)
{
    Q_ASSERT(x >= 0 && x < width());
    Q_ASSERT(y >= 0 && y < height());
    Q_ASSERT(frame >= 0 && frame < frames());
    Q_ASSERT(isValid());

    DcmTagPixelData *tagPixelDataPtr = tagPixelData();
    Q_ASSERT(tagPixelDataPtr);

    quint32 idx = pixelByteArrayIndex(x, y, frame);
    char *rawBytePtr = &(tagPixelDataPtr->data().data()[idx]);

    if (bitsAllocated() > 8) {
        DcmUnsignedShort *usPtr = (DcmUnsignedShort*)rawBytePtr;
        *usPtr = p;
    } else {
        // One byte per pixel
        DcmUnsignedByte *ubPtr = (DcmUnsignedByte*)rawBytePtr;
        if (p > 0x00FF) {
            *ubPtr = 0xFF;
        } else {
            *ubPtr = p & 0x00FF;
        }
    }
}

DcmMonochromeImage* DcmMonochromeImage::fromDcmImage(const DcmImage *imagePtr)
{
    Q_ASSERT(imagePtr);
    if (!imagePtr) {
        return 0;
    }

    DcmPhotometricInterpretation phi = imagePtr->photometricInterpretation();
    if (!phi.isGrayscale()) {
        return 0;   // Not a monochrome image
    }

    DcmMonochromeImage *monoImage = new DcmMonochromeImage(imagePtr->dataset());
    return monoImage;
}
