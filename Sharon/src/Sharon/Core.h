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

#ifdef SHARON_ENABLE_ASSERTS
#define SHARON_ASSERT(x, ...) { if(!(x)) { SHARON_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define SHARON_CORE_ASSERT(x, ...) { if(!(x)) { SHARON_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define SHARON_ASSERT(x, ...)
    #define SHARON_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)