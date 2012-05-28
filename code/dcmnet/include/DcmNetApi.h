#ifndef DCMNETAPI_H
#define DCMNETAPI_H

#ifdef _MSC_VER
    #ifdef dcmnet_EXPORTS
        #define DCM_NET_API __declspec(dllexport)
    #else
        #define DCM_NET_API __declspec(dllimport)
    #endif
#else
    #define DCM_NET_API
#endif // _MSC_VER

#endif // DCMNETAPI_H