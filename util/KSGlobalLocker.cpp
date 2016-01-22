#include "KSGlobalLocker.h"
#include <mutex>
KS_UTIL_BEGIN

static std::mutex locker;

void globalLock(void)
{
	locker.lock();
}

void globalUnlock(void)
{
	locker.unlock();
}

bool globalTrylock(void)
{
	return locker.try_lock();
}
KS_UTIL_END
