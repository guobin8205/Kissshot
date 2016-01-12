#pragma once


#ifndef __KISSHOT__ENGINE__DEBUG__
#define __KISSHOT__ENGINE__DEBUG__

#include "KSMacro.h"
#if KISSHOT_DEBUG
#include "bx/debug.h"
#endif

KS_BEGIN
void KS_DLL log(const char* msg, ...) KS_FORMAT_PRINTF(1,2);
KS_END

#if KISSHOT_DEBUG
#define KSLOG(msg,...) kisshot::log(msg,##__VA_ARGS__)
#define KSBREAK(comp) if(!!(comp)) bx::debugBreak()
#define KSWARMING(comp,msg,...) if(!!(comp)) kisshot::log(msg,##__VA_ARGS__)
#else
#define KSLOG(msg,...)
#define KSBREAK(comp)
#define KSWARMING(comp,msg,...)
#endif

#endif