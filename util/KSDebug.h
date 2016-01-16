#pragma once


#ifndef __KISSSHOT__ENGINE__DEBUG__
#define __KISSSHOT__ENGINE__DEBUG__

#include "KSMacro.h"
#if KISSSHOT_DEBUG
#include "bx/debug.h"
#include <assert.h>
#endif

KS_BEGIN
void KS_DLL log(const wchar_t* msg, ...) KS_FORMAT_PRINTF(1,2);
KS_END

#if KISSSHOT_DEBUG
#define KSLOG(msg,...) kissshot::log(msg, ##__VA_ARGS__)
#define KSBREAK(comp) if(!!(comp)) bx::debugBreak()
#define KSWARMING(comp,msg,...) if(!!(comp)) kissshot::log(msg,##__VA_ARGS__)
#define KSASSERT(comp) assert((comp))
#else
#define KSLOG(msg,...)
#define KSBREAK(comp) comp
#define KSWARMING(comp,msg,...) comp
#define KSASSERT(comp) comp
#endif

#endif