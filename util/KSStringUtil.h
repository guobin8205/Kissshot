#pragma once

#ifndef __KISSSHOT__ENGINE__STRINGUTIL__
#define __KISSSHOT__ENGINE__STRINGUTIL__

#include "KSUtilMacro.h"
#include <string>

KS_UTIL_BEGIN
::std::string KS_DLL WString2String(const std::wstring& str);
::std::wstring KS_DLL String2WString(const std::string& str);
KS_UTIL_END

#define KS_W2A(wstr)	KS_UTIL::WString2String(wstr)
#define KS_A2W(str)		KS_UTIL::String2WString(str)


#endif