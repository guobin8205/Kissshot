#include "KSStringUtil.h"

KS_UTIL_BEGIN
::std::string util::WString2String(const std::wstring & str)
{
	size_t size = str.length() * 2 + 1U;
	size_t len = 0;
	char* out = nullptr;
	while (true)
	{
		KS_SAFE_FREE(out);
		out = (char*)malloc(size * sizeof(char));
		setlocale(LC_ALL, "");
		len = wcstombs(out, str.c_str(), size);
		setlocale(LC_ALL, "C");
		if (len < (size - 1) ) break;
		size *= 2;
	}
	::std::string ret = "";
	if(out)
		ret.append(out,len);
	KS_SAFE_FREE(out);
	return ret;
}

::std::wstring util::String2WString(const std::string & str)
{
	size_t size = str.length() * 2 + 1U;
	size_t len = 0;
	wchar_t* out = nullptr;
	while (true)
	{
		KS_SAFE_FREE(out)
		out = (wchar_t*)malloc(size * sizeof(wchar_t));
		setlocale(LC_ALL, "");
		len = mbstowcs(out, str.c_str(), size);
		setlocale(LC_ALL, "C");
		if (len < (size - 1)) break;
		size *= 2;
	}
	::std::wstring ret = L"";
	if (out)
		ret.append(out, len);
	KS_SAFE_FREE(out);
	return ret;
}

KS_UTIL_END
