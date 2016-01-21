#pragma once


#ifndef __KISSSHOT__ENGINE__UTIL__DEBUG__
#define __KISSSHOT__ENGINE__UTIL__DEBUG__

#include "KSUtilMacro.h"
#if KISSSHOT_DEBUG
#include "../external/bx/include/bx/debug.h"
#include <assert.h>
#endif

KS_UTIL_BEGIN
void KS_DLL log(const wchar_t* msg, ...) KS_FORMAT_PRINTF(1, 2);
KS_UTIL_END


#if KISSSHOT_DEBUG
#define KSLOG(msg,...) KS_UTIL::log(msg, ##__VA_ARGS__)
#define KSBREAK(comp) if(!!(comp)) KS_UTIL::debugBreak()
#define KSWARMING(comp,msg,...) if(!!(comp)) KS_UTIL::log(msg,##__VA_ARGS__)
#define KSASSERT(comp) assert((comp))
#else
#define KSLOG(msg,...)
#define KSBREAK(comp) comp
#define KSWARMING(comp,msg,...) comp
#define KSASSERT(comp) comp
#endif

#endif