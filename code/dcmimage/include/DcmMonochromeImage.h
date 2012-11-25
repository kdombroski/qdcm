#ifndef DCMMONOCHROMEIMAGE_H
#define DCMMONOCHROMEIMAGE_H

#include "DcmImage.h"

/*! DICOM monochrome image.
 * Monochrome image contains only one color channel
 * and is encoded using photometric representation MONOCHROME1 or
 * MONOCHROME2
 */
class DcmMonochromeImage : public DcmImage
{
public:

    /**
     * Construct monochrome image with defined dimension.
     * \param width Image width in pixels.
     * \param height Image height in pixels.
     * \param frames Number of frame in the image.
     * \param bitsAllocated Number of bits allocated per single pixel (8 or 16).
     * \param bitsStored Number of bits used to encode pixel intensiti
     *      (less or equal to the number of allocated bits).
     * \param highBit High bit number.
     * \param pi Photometric interpretation Monochrome1 or Monochrome2 (if other is given
     *      the image is constructed as invalid).
     */
    DcmMonochromeImage(int width,
                       int height,
                       int frames = 1,
                       int bitsAllocated = 16,
                       int bitsStored = 16,
                       int highBit = 15,
                       const DcmPhotometricInterpretation &pi = DcmPhotometricInterpretation::Monochrome2);

    /**
     * Construct monochromatic image from DICOM dataset.
     * @param datasetPtr Pointer to a vaid DICOM dataset.
     */
    DcmMonochromeImage(const DcmDataset *datasetPtr);

    /**
     * Copy ocnstructor.
     * @param monoImage Image to be copied.
     */
    DcmMonochromeImage(const DcmMonochromeImage &monoImage);

    /**
     * Assignment operator.
     * @param monoImage Image to be assigned.
     * @return Reference to this image object.
     */
    DcmMonochromeImage& operator =(const DcmMonochromeImage &monoImage);

    /**
     * Destructor.
     */
    ~DcmMonochromeImage();

    /**
     * Tell whether this image is valid.
     * Additional to the checks performed by image base class, this method
     * also checks image phototetric representation to be Monochrome1 or Monochrome2.
     * @return true if image is valid.
     */
    bool isValid() const;

    /**
     * Returns raw pixel value at given position.
     * This method does not perform any correcting of the pixel value according
     * to clase/offset not to the photometric interpretation.
     * @param x Pixel x coordinate.
     * @param y Pixel y coordinate.
     * @param frame Frame number.
     * @return Pixel raw value.
     */
    DcmUnsignedShort rawPixel(int x, int y, int frame = 0) const;

    /**
     * Assign raw pixel value at given position.
     * @param p Pixel value to be assigned.
     * @param x Pixel x coordinate.
     * @param y Pixel y coordinate.
     * @param frame Frame number.
     */
    void setRawPixel(DcmUnsignedShort p, int x, int y, int frame = 0);

    /**
     * Convert generic DICOM image to monochromatic image.
     * This method does not perform pixels convertion. It just reinterprets
     * the image as being monochromatic. The photometric interpretation of the
     * input image must be Grayscale. In other case a null pointer is returned
     * by this method.
     * This method makes a deep copy on an image. The original image can be
     * safely deleted afterwards.
     * @param imagePtr Pointer to an image to be converted.
     * @return Pointer to a newly allocated monochromatic image or null if unable to convert.
     */
    static DcmMonochromeImage *fromDcmImage(const DcmImage *imagePtr);

};

#endif // DCMMONOCHROMEIMAGE_H
