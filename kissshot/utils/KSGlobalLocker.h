#pragma once
#ifndef __KISSSHOT__ENGINE__UTIL__GLOBALE__LOCKER__
#define __KISSSHOT__ENGINE__UTIL__GLOBALE__LOCKER__

#include "KSUtilMacro.h"

KS_UTIL_BEGIN

extern inline void KS_DLL LockResources(void);
extern inline void KS_DLL UnlockResources(void);
extern inline bool KS_DLL TryLockResources(void);

KS_UTIL_END

#endif