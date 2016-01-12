#pragma once

#ifndef __KISSHOT__ENGINE__STORAGE__
#define __KISSHOT__ENGINE__STORAGE__
#include "KSMacro.h"
#include <string>
#include <vector>
KS_BEGIN

class Data final
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

	inline void reset(void)
	{
		mSize = 0;
		KS_SAFE_FREE(mData);
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

	std::string getWritablePath(void);
	std::string getLocationPath(void);

	void addSearchPath(const std::string path);

	bool isFileExist(const std::string& file);
	bool getFullPathWithFileName(const std::string& file, std::string& output);

	Data getDataFromFile(const std::string& file);

private:
	bool _init(void);
	

private:
	std::vector<std::string> mPaths;
};

KS_END

#endif