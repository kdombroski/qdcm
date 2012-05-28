#ifndef DCMMODULEAPI_H
#define DCMMODULEAPI_H

#ifdef _MSC_VER
    #ifdef dcmmod_EXPORTS
        #define DCM_MODULE_API __declspec(dllexport)
    #else
        #define DCM_MODULE_API __declspec(dllimport)
    #endif
#else
    #define DCM_MODULE_API
#endif // _MSC_VER

#endif // DCMMODULEAPI_H
