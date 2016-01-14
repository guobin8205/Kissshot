#include "KSStringUtil.h"
KS_BEGIN

::std::string util::WString2String(const std::wstring & str)
{
	size_t size = str.length() + 1U;
	size_t len = 0;
	char* out = nullptr;
	while (true)
	{
		KS_SAFE_FREE(out);
		out = (char*)malloc(size * sizeof(char));
		len = wcstombs(out, str.c_str(), size);
		if (len >= 0) break;
	}
	::std::string ret = "";
	if(out)
		ret.copy(out,len);
	KS_SAFE_FREE(out);
	return ret;
}

::std::wstring util::String2WString(const std::string & str)
{
	size_t size = str.length() + 1U;
	size_t len = 0;
	wchar_t* out = nullptr;
	while (true)
	{
		KS_SAFE_FREE(out);
		out = (wchar_t*)malloc(size * sizeof(wchar_t));
		len = mbstowcs(out, str.c_str(), size);
		if (len >= 0) break;
	}
	::std::wstring ret = L"";
	if (out)
		ret.copy(out, len);
	KS_SAFE_FREE(out);
	return ret;
}

KS_END
