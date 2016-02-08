#include "KSGlobalLocker.h"
#include <mutex>

KS_UTIL_BEGIN

static std::mutex ResourcesLocker;

inline void LockResources(void)
{
	ResourcesLocker.lock();
}

inline void UnlockResources(void)
{
	ResourcesLocker.unlock();
}

inline bool TryLockResources(void)
{
	return ResourcesLocker.try_lock();
}

KS_UTIL_END
