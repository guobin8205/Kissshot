#pragma once
#ifndef __KISSSHOT__ENGINE__BASE__ARRAY__
#define __KISSSHOT__ENGINE__BASE__ARRAY__

#include "KSBaseMacro.h"

KS_BASE_BEGIN

template<typename T,uint32 size>
class Array final
{
public:
	typedef T* Iterator;

	inline uint32 getSize(void) { return size; }
	inline Iterator begin(void) { return *mArray[0]; }
	inline Iterator end(void) { return *mArray[size]; }

	inline T& operator[](uint32 index) { return mArray[index % size]; }

private:
	T mArray[size];
};

KS_BASE_END

#endif