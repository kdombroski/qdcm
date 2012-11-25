#ifndef DCMIMAGE_H
#define DCMIMAGE_H

#include <QByteArray>
#include <QImage>
#include "DcmImageApi.h"
#include "DcmPhotometricInterpretation.h"
#include "DcmTagPixelData.h"
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
     * \param highBit Highest bit number.
     * \param samplesPerPixel Number of samples per pixel. Each sample takes <bitsAllocated> bits.
     * \param pi Photometric interpretation.
     */
    DcmImage(int width,
             int height,
             int frames,
             int bitsAllocated,
             int bitsStored,
             int highBit,
             int samplesPerPixel,
             const DcmPhotometricInterpretation &pi);

    /**
     * Construct image from DICOM dataset.
     * The dataset will be copied, and the original pointer will not
     * be retained by the image constructed.
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
     * Returns the highest bit number.
     * \return Highest bit number.
     */
    int highBit() const;

    /**
     * Returns number of samples per pixel.
     * This value correlates with photometric interpretation.
     * For instance for RGB interpretation there are 3 samples per pixel.
     * \return Number of samples per pixel.
     */
    int samplesPerPixel() const;

    /**
     * Returns image photometric interpretation.
     * \return Photometric interpretation.
     */
    DcmPhotometricInterpretation photometricInterpretation() const;

    /**
     * Returns image pixels rescale intercept tag (0028, 1052) value.
     * If tag is absent, 0.0 value is returned.
     * \return  Image pixel value rescale intercept.
     */
    double rescaleIntercept() const;

    /**
     * Assign rescale intercept value.
     * \param ri Rescale intercept value to be set.
     */
    void setRescaleIntercept(double ri);

    /**
     * Returns image pixels rescale slope tag (0028, 1053) value.
     * If tag is absent, 1.0 value is returned.
     * \return Image pixel value rescale slope.
     */
    double rescaleSlope() const;

    /**
     * Assign rescale slope value.
     * \param rs Rescale slope value to be set.
     */
    void setRescaleSlope(double rs);

    /**
     * Returns image pixels rescale type tag (0028, 1054) value.
     * If tag is absent, an empty string is returned.
     * \return Rescale type as defined in DICOM dataset.
     */
    QString rescaleTypeString() const;

    /**
     * Assign rescale type string.
     * \param rt Rescale type string to be assigned.
     */
    void setRescaleTypeString(const QString &rt);

    /**
     * Returns pointer to DICOM dataset.
     * \return Pointer to dataset.
     */
    DcmDataset* dataset() const;

    /**
     * Returns pointer to pixel data tag.
     * \return Pointer to pixel data tag.
     */
    DcmTagPixelData* tagPixelData() const;

    /**
     * Tell whether this image is valid.
     * The validity check may be useful if the image object is constructed
     * from a dataset. If some tags are missing or no pixel data present, or
     * sizes are not respedted, the image may be considered as invalid.
     * \return true if the image is valid.
     */
    virtual bool isValid() const;

    /**
     * Returns pixel raw data index in pixel buffer byte array.
     * The method does not check whether provided coordinates are
     * valid ones.
     * \param x Pixel x coordinate.
     * \param y Pixel y coordinate.
     * \param frame Pixel frame number.
     * \return Pixel byte array index.
     */
    quint32 pixelByteArrayIndex(int x, int y, int frame = 0) const;

private:

    /**
     * Allocate pixel data according to dimensions
     * and bit depth set.
     */
    void allocatePixelData();

    DcmDataset *m_datasetPtr;   ///< DICOM dataset associated with this image.
    DcmTagPixelData *m_tagPixelDataPtr; ///< Pointer to pixel data tag within the image dataset (for easy access).
};

#endif // DCMIMAGE_H
