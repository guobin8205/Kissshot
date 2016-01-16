#include "KSStringUtil.h"
#include "KSDebug.h"
#include "bx/debug.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
KS_BEGIN

static size_t MAX_LOG_LENGTH = 16 * 1024;

static void _log(const wchar_t* msg, va_list args)
{
	int bufferSize = MAX_LOG_LENGTH;
	size_t len = 0U;
	wchar_t* buf = nullptr;
	do
	{
		buf = (wchar_t*)malloc(bufferSize * sizeof(wchar_t));
		if (buf == nullptr)
			return; // not enough memory

		len = _vsnwprintf(buf, bufferSize - 3, msg, args);
		if (len < 0)
		{
			bufferSize *= 2;
			KS_SAFE_FREE(buf);
		}
		else
			break;
	} while (true);
	::std::wstring str(buf, len);
	KS_SAFE_FREE(buf);
	bx::debugOutput((KS_W2A(str) + '\n').c_str());
	
}

void KS_DLL log(const wchar_t * msg, ...)
{
	va_list args;
	va_start(args, msg);
	_log(msg, args);
	va_end(args);
}

KS_END
