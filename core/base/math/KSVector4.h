#pragma once
#ifndef __KISSSHOT__ENGINE__MATH__VECTOR4__
#define __KISSSHOT__ENGINE__MATH__VECTOR4__

#include "KSMathMacro.h"
#include "KSMacro.h"
#include <bx/fpumath.h>

KS_MATH_BEGIN

class Vector3;

class KS_DLL Vector4 final
{
public:
	Vector4(void)
		: x(vector[0]), y(vector[1]), z(vector[2]), w(vector[3])
	{
		bx::quatIdentity(vector);
	}
	Vector4(const float(&ff)[4])
		: Vector4()
	{
		bx::quatMove(vector, ff);
	}
	Vector4(const Vector3 &vec);

	inline Vector4& normalizing(void)
	{
		bx::quatNorm(vector, vector);
		return *this;
	}

	inline Vector4& invert(void)
	{
		bx::quatInvert(vector, vector);
		return *this;
	}

	inline Vector4& absoulte(void)
	{
		x = bx::fabsolute(x); y = bx::fabsolute(y); z = bx::fabsolute(z); w = bx::fabsolute(w);
		return *this;
	}

	inline Vector4& set(float xx, float yy, float zz, float ww = 1.0f) { x = xx; y = yy; z = zz; w = ww; return *this; }

	//ignore w
	inline float length(void) { return bx::vec3Length(vector); }
	inline float dot(const Vector4& v2) { return bx::quatDot(vector, v2.vector); }

	inline Vector4& operator=(const Vector3& vec3);

public:
	float &x, &y, &z, &w;
	float vector[4];

	const static Vector4 Zero;
	const static Vector4 Identity;
};

KS_MATH_END


#endif