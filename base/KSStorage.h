#pragma once

#ifndef __KISSHOT__ENGINE__STORAGE__
#define __KISSHOT__ENGINE__STORAGE__
#include "KSMacro.h"
#include <string>
#include <vector>
KS_BEGIN

class KS_DLL Data final
{
public:
	Data(void)
		:Data(nullptr, 0){}
	Data(unsigned char* data, size_t size)
		:mData(data)
		,mSize(size)
	{}
	~Data()
	{
		reset();
	}

	inline void reset(unsigned char* data = nullptr,size_t size = 0U)
	{
		size = 0;
		KS_SAFE_FREE(mData);
		mData = data;
	}
private:
	unsigned char* mData;
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

KS_END

#endif