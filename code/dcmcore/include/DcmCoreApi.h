#ifndef DCMCOREAPI_H
#define DCMCOREAPI_H

#ifdef _MSC_VER
    #ifdef dcmcore_EXPORTS
        #define DCM_CORE_API __declspec(dllexport)
    #else
        #define DCM_CORE_API __declspec(dllimport)
    #endif
#else
    #define DCM_CORE_API
#endif // _MSC_VER

#endif // DCMCOREAPI_H
