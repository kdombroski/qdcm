#ifndef DCMIMAGEAPI_H
#define DCMIMAGEAPI_H

#ifdef _MSC_VER
    #ifdef dcmimage_EXPORTS
        #define DCM_IMAGE_API __declspec(dllexport)
    #else
        #define DCM_IMAGE_API __declspec(dllimport)
    #endif
#else
    #define DCM_IMAGE_API
#endif // _MSC_VER

#endif // DCMIMAGEAPI_H
