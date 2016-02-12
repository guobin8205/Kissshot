#include "KSStringUtil.h"

KS_UTIL_BEGIN
::std::string WString2String(const std::wstring & str)
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

::std::wstring String2WString(const std::string & str)
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

inline uint32 GetHashCode(const unsigned char* _First, size_t _Count)
{
#if KS_ARCH_64
	static_assert(sizeof(size_t) == 8, "This code is for 64-bit size_t.");
	const size_t _FNV_offset_basis = 14695981039346656037ULL;
	const size_t _FNV_prime = 1099511628211ULL;

#else /* defined(_WIN64) */
	static_assert(sizeof(size_t) == 4, "This code is for 32-bit size_t.");
	const size_t _FNV_offset_basis = 2166136261U;
	const size_t _FNV_prime = 16777619U;
#endif /* defined(_WIN64) */

	size_t _Val = _FNV_offset_basis;
	for (size_t _Next = 0; _Next < _Count; ++_Next)
	{	// fold in another byte
		_Val ^= (size_t)_First[_Next];
		_Val *= _FNV_prime;
	}
	return (_Val);
}

inline uint32 KS_DLL GetHashCode(const std::string & str)
{
	return GetHashCode((const unsigned char*)str.c_str(), str.size() * sizeof(char));
}

inline uint32 KS_DLL GetHashCode(const std::wstring & str)
{
	return GetHashCode((const unsigned char*)str.c_str(), str.size() * sizeof(wchar_t));
}

KS_UTIL_END


