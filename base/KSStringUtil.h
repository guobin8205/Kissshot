#pragma once

#ifndef __KISSSHOT__ENGINE__STRINGUTIL__
#define __KISSSHOT__ENGINE__STRINGUTIL__

#include "KSMacro.h"
#include <string>

KS_BEGIN
namespace util
{
	::std::string WString2String(const std::wstring& str);
	::std::wstring String2WString(const std::string& str);
}

#define KS_W2A(wstr)	::kissshot::util::WString2String(wstr)
#define KS_A2W(str)		::kissshot::util::String2WString(str)

KS_END

#endif