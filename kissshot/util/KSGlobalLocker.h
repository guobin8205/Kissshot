#pragma once
#ifndef __KISSSHOT__ENGINE__UTILS__GLOBALLOCKER__
#define __KISSSHOT__ENGINE__UTILS__GLOBALLOCKER__

#include "KSUtilMacro.h"

KS_UTIL_BEGIN
void KS_DLL globalLock(void);
void KS_DLL globalUnlock(void);
bool KS_DLL globalTrylock(void);
KS_UTIL_END

#define KSLOCK ::kissshot::utils::globalLock()
#define KSUNLOCK ::kissshot::utils::globalUnlock()
#define KSTRYLOCK ::kissshot::utils::globalTrylock()

#endif