#pragma once

#ifndef __KISSSHOT__ENGINE__TRANSFORM__
#define __KISSSHOT__ENGINE__TRANSFORM__

#include "KSBaseMacro.h"
#include "KSMath.h"
#include <atomic>

KS_BASE_BEGIN

class KS_DLL Transform
{
public:
	Transform(void);
	Transform(const math::Vector3& p, const math::Vector3& s, const math::Vector3& r);

	math::Matrix4x4 getMatrix(void);

	inline Transform& setScale(float s)
	{
		rotate = math::Vector3(s, s, s);
		return *this;
	};

public:
	math::Vector3 position;
	math::Vector3 scale;
	math::Vector3 rotate;
};

KS_BASE_END

#endif