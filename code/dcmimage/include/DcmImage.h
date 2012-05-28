#ifndef DCMIMAGE_H
#define DCMIMAGE_H

#include <QByteArray>
#include <QImage>
#include "DcmImageApi.h"
#include "DcmPhotometricInterpretation.h"
#include "DcmDataset.h"

/*! DICOM image base class.
 * This is a base class for DICOM image data storage.
 */
class DCM_IMAGE_API DcmImage
{
public:

    /**
     * Construct an image.
     * \param width Image width in pixels.
     * \param height Image height in pixels.
     * \param frames Number of frames.
     * \param bitsAllocated Number of bits per pixel (8, 16, or 32).
     * \param bitsStored Number of effective bits used to encode pixel value (<= bitsAllocated).
     * \param pi Photometric interpretation.
     */
    DcmImage(int width, int height, int frames, int bitsAllocated, int bitsStored, const DcmPhotometricInterpretation &pi);

    /**
     * Construct image from DICOM dataset
     * \param datasetPtr DICOM dataset pointer.
     */
    DcmImage(const DcmDataset *datasetPtr);

    /**
     * Copy constructor.
     * \param image Image to be copied.
     */
    DcmImage(const DcmImage &image);

    /**
     * Assignment operator.
     * \param image Image to be assigned.
     * \return This image.
     */
    DcmImage& operator =(const DcmImage &image);

    /**
     * Destructor.
     */
    virtual ~DcmImage();

    /**
     * Returns image width in pixels.
     * \return Image width in pixels.
     */
    int width() const;

    /**
     * Returns image height in pixels.
     * \return Image height in pixels.
     */
    int height() const;

    /**
     * Returns number of frames in the image.
     * \return Number of frames.
     */
    int frames() const;

    /**
     * Returns number of bits allocated per pixel.
     * \return Number of bits per pixel.
     */
    int bitsAllocated() const;

    /**
     * Returns number of effective bits used to represent a pixel value.
     * \return Number of effective bits.
     */
    int bitsStored() const;

    /**
     * Returns image photometric interpretation.
     * \return Photometric interpretation.
     */
    DcmPhotometricInterpretation photometricInterpretation() const;

    /**
     * Returns pointer to DICOM dataset.
     * \return Pointer to dataset.
     */
    DcmDataset* dataset();

private:

    /**
     * Allocate pixel data according to dimensions
     * and bit depth set.
     */
    void allocatePixelData();

    DcmDataset *m_datasetPtr;   ///< DICOM dataset associated with this image.
};

#endif // DCMIMAGE_H
