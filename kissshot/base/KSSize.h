#pragma once
#ifndef __KISSSHOT__ENGINE__BASE__SIZE__
#define __KISSSHOT__ENGINE__BASE__SIZE__

#include "KSBaseMacro.h"

KS_BASE_BEGIN

class KS_DLL Size
{
public:
	Size(float32 w = 0.0f, float32 h = 0.0f)
		: width(w)
		, height(h)
	{
	}

public:
	float32 width, height;
};

KS_BASE_END

#endif