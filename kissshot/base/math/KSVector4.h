#pragma once
#ifndef __KISSSHOT__ENGINE__MATH__VECTOR4__
#define __KISSSHOT__ENGINE__MATH__VECTOR4__

#include "KSMathMacro.h"

KS_MATH_BEGIN

class Vector3;
class Matrix4x4;

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

	///this function will change this;
	///return *this
	inline Vector4& normalizing(void)
	{
		bx::quatNorm(vector, vector);
		return *this;
	}

	///this function will change this;
	///return *this
	inline Vector4& invert(void)
	{
		bx::quatInvert(vector, vector);
		return *this;
	}

	///this function will change this;
	///return *this
	inline Vector4& absoulte(void)
	{
		x = bx::fabsolute(x); y = bx::fabsolute(y); z = bx::fabsolute(z); w = bx::fabsolute(w);
		return *this;
	}

	inline Vector4 getNormalizing(void)
	{
		Vector4 res = *this;
		return res.normalizing();
	}

	inline Vector4 getInvert(void)
	{
		Vector4 res = *this;
		return res.invert();
	}

	inline Vector4 getAbsoulte(void) const
	{
		Vector4 res = *this;
		return res.absoulte();
	}

	inline Vector4& scale(float xx, float yy = 1.0f, float zz = 1.0f, float ww = 1.0f)
	{
		x *= xx; y *= yy; z *= zz; w *= ww;
		return *this;
	}

	inline Vector4& scale(const Vector4& s)
	{
		return scale(s.x, s.y, s.z, s.w);
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

#define OPERATOR_PARAMETER  const Vector4& first, const Vector4& second
#define OPERATOR_PARAMETER_NUM const Vector4& first, const float num
#define OPERATOR_PARAMETER_UNCONST Vector4& first, const Vector4& second
#define OPERATOR_PARAMETER_NUM_UNCONST Vector4& first, const float num
#define KS_MATH_GET_DEV float xx = first.x - second.x, yy = first.y - second.y, zz = first.z - second.z, ww = first.w - second.w

inline bool operator == (OPERATOR_PARAMETER)
{
	KS_MATH_GET_DEV;
	return bx::fabsolute(xx) <= KS_MATH_COMPARE_DEV
		&& bx::fabsolute(yy) <= KS_MATH_COMPARE_DEV
		&& bx::fabsolute(zz) <= KS_MATH_COMPARE_DEV
		&& bx::fabsolute(ww) <= KS_MATH_COMPARE_DEV;
}

inline bool operator < (OPERATOR_PARAMETER)
{
	KS_MATH_GET_DEV;
	return (xx < -KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy < -KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy <= KS_MATH_COMPARE_DEV && yy >= -KS_MATH_COMPARE_DEV && zz < KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy <= KS_MATH_COMPARE_DEV && yy >= -KS_MATH_COMPARE_DEV && zz <= KS_MATH_COMPARE_DEV && zz >= -KS_MATH_COMPARE_DEV && ww < -KS_MATH_COMPARE_DEV);
}

inline bool operator > (OPERATOR_PARAMETER)
{
	KS_MATH_GET_DEV;
	return (xx > KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy > KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy <= KS_MATH_COMPARE_DEV && yy >= -KS_MATH_COMPARE_DEV && zz > KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy <= KS_MATH_COMPARE_DEV && yy >= -KS_MATH_COMPARE_DEV && zz <= KS_MATH_COMPARE_DEV && zz >= -KS_MATH_COMPARE_DEV && ww > KS_MATH_COMPARE_DEV);;
}

inline bool operator <= (OPERATOR_PARAMETER)
{
	return (first < second) || (first == second);
}

inline bool operator >= (OPERATOR_PARAMETER)
{
	return (first > second) || (first == second);
}

inline Vector4 operator + (OPERATOR_PARAMETER)
{
	Vector4 vec;
	vec.x = first.x + second.x;
	vec.y = first.y + second.x;
	vec.z = first.z + second.x;
	vec.w = first.w + second.x;
	return vec;
}

inline Vector4 operator + (OPERATOR_PARAMETER_NUM)
{
	Vector4 vec;
	vec.x = first.x + num;
	vec.y = first.y + num;
	vec.z = first.z + num;
	vec.w = first.w + num;
	return vec;
}

inline Vector4 operator - (OPERATOR_PARAMETER)
{
	Vector4 vec;
	vec.x = first.x - second.x;
	vec.y = first.y - second.x;
	vec.z = first.z - second.x;
	vec.w = first.w - second.x;
	return vec;
}

inline Vector4 operator - (OPERATOR_PARAMETER_NUM)
{
	Vector4 vec;
	vec.x = first.x - num;
	vec.y = first.y - num;
	vec.z = first.z - num;
	vec.w = first.w - num;
	return vec;
}

//cross mul
inline Vector4 operator * (OPERATOR_PARAMETER)
{
	Vector4 vec;
	bx::quatMul(vec.vector, first.vector, second.vector);
	return vec;
}

inline Vector4 operator * (OPERATOR_PARAMETER_NUM)
{
	Vector4 vec;
	vec.x = first.x * num;
	vec.y = first.y * num;
	vec.z = first.z * num;
	vec.w = first.w * num;
	return vec;
}

inline Vector4& operator += (OPERATOR_PARAMETER_UNCONST)
{
	first.x = first.x + second.x;
	first.y = first.y + second.x;
	first.z = first.z + second.x;
	first.w = first.w + second.x;
	return first;
}

inline Vector4& operator += (OPERATOR_PARAMETER_NUM_UNCONST)
{
	first.x = first.x + num;
	first.y = first.y + num;
	first.z = first.z + num;
	first.w = first.w + num;
	return first;
}

inline Vector4& operator -= (OPERATOR_PARAMETER_UNCONST)
{
	first.x = first.x - second.x;
	first.y = first.y - second.x;
	first.z = first.z - second.x;
	first.w = first.w - second.x;
	return first;
}

inline Vector4& operator -= (OPERATOR_PARAMETER_NUM_UNCONST)
{
	first.x = first.x - num;
	first.y = first.y - num;
	first.z = first.z - num;
	first.w = first.w - num;
	return first;
}

//cross mul
inline Vector4& operator *= (Vector4& first, const Vector4& second)
{
	bx::quatMul(first.vector, first.vector, second.vector);
	return first;
}

inline Vector4& operator *= (OPERATOR_PARAMETER_NUM_UNCONST)
{
	first.x = first.x * num;
	first.y = first.y * num;
	first.z = first.z * num;
	first.w = first.w * num;
	return first;
}

KS_DLL Vector4 operator * (const Vector4& first, const Matrix4x4& second);
KS_DLL Vector4& operator *= (Vector4& first, const Matrix4x4& second);

#undef OPERATOR_PARAMETER
#undef OPERATOR_PARAMETER_NUM
#undef OPERATOR_PARAMETER_UNCONST
#undef OPERATOR_PARAMETER_NUM_UNCONST
#undef KS_MATH_GET_DEV

KS_MATH_END


#endif