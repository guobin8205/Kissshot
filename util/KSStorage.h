#pragma once

#ifndef __KISSHOT__ENGINE__UTIL__STORAGE__
#define __KISSHOT__ENGINE__UTIL__STORAGE__
#include "KSUtilMacro.h"
#include <string>
#include <vector>
#include <memory>

KS_UTIL_BEGIN
class KS_DLL Data final
{
public:
	Data(void)
		:Data(nullptr, 0) {}
	Data(unsigned char* data, size_t size)
		: mData(data)
		, mSize(size)
	{}
	~Data()
	{
		reset();
	}

	inline void reset(unsigned char* data = nullptr, size_t size = 0U)
	{
		size = size;
		mData.reset(data);
	}
private:
	std::shared_ptr<unsigned char> mData;
	size_t mSize;
};

class KS_DLL Storage final
{
public:
	static Storage* getInstance(void);
	static void destoryInstance(void);

	std::wstring getWritablePath(void);
	std::wstring getLocationPath(void);

	void addSearchPath(const std::wstring path);

	bool isFileExist(const std::wstring& file);
	bool getFullPathWithFileName(const std::wstring& file, std::wstring& output);
	bool isAbsolutePath(const std::wstring& path);


	Data getDataFromFile(const std::wstring& file);

	bool createFolderInWritablePath(const std::wstring& path);
	bool deleteFileWithPath(const std::wstring& file);

private:
	bool _init(void);


private:
	std::vector<std::wstring> mPaths;
};
KS_UTIL_END

#endif