#include "KSStorage.h"

#if KS_PLATFORM_WINRT

KS_BEGIN

static Storage* _instance = nullptr;

Storage * Storage::getInstance(void)
{
	if (!_instance)
	{
		_instance = new Storage();
		
	}
	return nullptr;
}

void Storage::destoryInstance(void)
{
}

bool Storage::_init(void)
{
	return false;
}

KS_END
#endif
