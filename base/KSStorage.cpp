#include "KSStorage.h"
#include "KSDebug.h"
#include "KSStringUtil.h"

#if KS_PLATFORM_WINRT
#include <Windows.h>
#include <ppltasks.h>
#endif

KS_BEGIN

static Storage* _instance = nullptr;
Storage * Storage::getInstance(void)
{
	if (!_instance)
	{
		_instance = new Storage();
		
	}
	return _instance;
}

void Storage::destoryInstance(void)
{
	KS_SAFE_DELETE(_instance);
}

void Storage::addSearchPath(const std::wstring path)
{
	auto& itor = std::find(mPaths.begin(), mPaths.end(), path);
	if (itor != mPaths.end())
		KSLOG(L"KS Warmming: search path <%s> is exist.", path.c_str());
	else
		mPaths.push_back(path);
}

bool Storage::isFileExist(const std::wstring & file)
{
	std::wstring str = L"";
	return getFullPathWithFileName(file, str);
}

bool Storage::getFullPathWithFileName(const std::wstring& file, std::wstring& output)
{
	if (isAbsolutePath(file))
	{
		output = file;
		return false;
	}
	else
	{
#if KISSSHOT_DEBUG
		const auto& fs = getLocationPath();
		const auto& ss = getWritablePath();
#else
		const auto& fs = getWritablePath();
		const auto& ss = getLocationPath();
#endif
		std::wstring fullpath;
		FILE* fd = nullptr;
		for (auto& search : mPaths)
		{
			fullpath = fs + search + file;
			if (fd = fopen(KS_W2A(fullpath).c_str(), "rd"))
			{
				output = fullpath;
				fclose(fd);
				return true;
			}
		}

		for (auto& search : mPaths)
		{
			fullpath = ss + search + file;
			if (fd = fopen(KS_W2A(fullpath).c_str(), "rd"))
			{
				output = fullpath;
				fclose(fd);
				return true;
			}
		}
	}
	KSLOG(L"KS Warmming: file <%s> is not found.", file.c_str());
	return false;
}

Data Storage::getDataFromFile(const std::wstring & file)
{
	std::wstring fullpath = L"";
	Data data;
	if (!getFullPathWithFileName(file, fullpath)) return data;

	FILE* fd = nullptr;
	fd = fopen(KS_W2A(fullpath.c_str()).c_str(),"rd");
	KSASSERT(!fd);
	
	size_t size = 0;
	fseek(fd, 0, SEEK_END);
	size = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	auto output = (unsigned char*)malloc(sizeof(unsigned char) * size);
	size_t readSize = fread(output, sizeof(unsigned char), size, fd);
	if (readSize <= 0)
		KSLOG(L"KS Warmming: read file <%s> data failed.", file.c_str());
	else
		data.reset(output, readSize);
	return data;
}

bool Storage::_init(void)
{
	return false;
}

#if KS_PLATFORM_WINRT
std::wstring Storage::getWritablePath(void)
{
	Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	return std::wstring();
}

std::wstring Storage::getLocationPath(void)
{
	auto location = Windows::ApplicationModel::Package::Current->InstalledLocation->Path;
	return std::wstring(location->Data());
}

bool Storage::isAbsolutePath(const std::wstring & path)
{
	if (path.length() <= 2) return false;
	const auto& first = path[0];
	const auto& second = path[1];
	if ((first >= L'a' && first <= L'z') || (first >= L'A' && first <= L'Z')
		&& second == L':')
		return true;
	return false;
}

bool Storage::createFolderInWritablePath(const std::wstring & path)
{
	
	return false;
}

bool Storage::deleteFileWithPath(const std::wstring & file)
{
	return false;
}
#endif
KS_END

