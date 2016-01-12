#include "pch.h"
#include "KSDebug.h"
#include "bx/debug.h"
#include <string.h>
#include <stdio.h>
#include <new>
KS_BEGIN

size_t MAX_LOG_LENGTH = 16 * 1024;

static void _log(const char* msg, va_list args)
{
	int bufferSize = MAX_LOG_LENGTH;
	char* buf = nullptr;
	do
	{
		buf = new(std::nothrow)char[bufferSize];
		if (buf == nullptr)
			return; // not enough memory

		int ret = vsnprintf(buf, bufferSize - 3, msg, args);
		if (ret < 0)
		{
			bufferSize *= 2;
			delete[] buf;
		}
		else
			break;
	} while (true);
	bx::debugOutput(buf);
	delete[] buf;
}

void KS_DLL log(const char * msg, ...)
{
	va_list args;
	va_start(args, msg);
	_log(msg, args);
	va_end(args);
}

KS_END
