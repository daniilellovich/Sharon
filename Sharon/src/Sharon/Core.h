#pragma once

#ifdef SHARON_PLATFORM_WINDOWS
    #ifdef SHARON_BUILD_DLL
        #define SHARON_API __declspec(dllexport)
    #else
        #define SHARON_API __declspec(dllimport)
    #endif
#else
    #error Sharon supports only Windows(
#endif

#define BIT(x) (1 << x)