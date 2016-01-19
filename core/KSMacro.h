#pragma once

#ifndef __KISSSHOT__ENGINE__MACRO__
#define __KISSSHOT__ENGINE__MACRO__
#include "bx/platform.h"

#define KS_PLATFORM_ANDROID		BX_PLATFORM_ANDROID
#define KS_PLATFORM_IOS			BX_PLATFORM_IOS
#define KS_PLATFORM_OSX			BX_PLATFORM_OSX
#define KS_PLATFORM_WINDESKTOP	BX_PLATFORM_WINDOWS
#define KS_PLATFORM_WINRT		BX_PLATFORM_WINRT

#define KS_SAFE_DELETE(__ptr__) \
	if(__ptr__) \
	{ \
		delete __ptr__; \
		__ptr__ = nullptr; \
	}

#define KS_SAFE_DELETE_ARRAY(__ptr__) \
	if(__ptr__) \
	{ \
		delete[] __ptr__; \
		__ptr__ = nullptr; \
	}

#define KS_SAFE_FREE(__ptr__) \
	if(__ptr__) \
	{ \
		free(__ptr__); \
		__ptr__ = nullptr; \
	}


#ifdef __cplusplus
#define KS_BEGIN	namespace kissshot {
#define KS_END		}
#else
#define KS_BEGIN
#define KS_END
#endif

#if !defined(KISSSHOT_DEBUG) && (defined(_DEBUG) || defined(DEBUG) || defined(__DEBUG))
#define KISSSHOT_DEBUG 1
#endif

#if KS_PLATFORM_WINRT || KS_PLATFORM_WINDESKTOP
	#if _WINDLL
		#define KS_DLL __declspec(dllexport)
	#else
		#define KS_DLL
	#endif
#else
	#define KS_DLL
#endif

#if defined(__GNUC__) && (__GNUC__ >= 4)
#define KS_FORMAT_PRINTF(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
#elif defined(__has_attribute)
#if __has_attribute(format)
#define KS_FORMAT_PRINTF(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
#endif // __has_attribute(format)
#else
#define KS_FORMAT_PRINTF(formatPos, argPos)
#endif

#endif