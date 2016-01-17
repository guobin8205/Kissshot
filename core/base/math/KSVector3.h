#pragma once

#ifndef __KISSSHOT__ENGINE__MATH__VECTOR3__
#define __KISSSHOT__ENGINE__MATH__VECTOR3__

#include "KSMathMacro.h"
#include "KSMacro.h"
#include <bx/fpumath.h>
#include <memory>

KS_MATH_BEGIN

class Matrix4x4;
class Vector4;

class KS_DLL Vector3 final
{
public:
	Vector3(void) : x(vector[0]), y(vector[1]), z(vector[2]) { std::memset(vector, 0, sizeof(float) * 3); }
	Vector3(const float(&ff)[3]) : Vector3() { bx::vec3Move(vector, ff); }
	inline Vector3& normalizing(void)
	{
		bx::vec3Norm(vector, vector);
		return *this;
	}

	inline Vector3& invert(void)
	{
		bx::vec3Neg(vector, vector);
		return *this;
	}

	inline Vector3& absoulte(void)
	{
		bx::vec3Abs(vector, vector);
		return *this;
	}

	inline Vector3& set(float xx, float yy, float zz) { x = xx; y = yy; z = zz; return *this; }

	inline float length(void) { return bx::vec3Length(vector); }
	inline float dot(const Vector3& v2) { return bx::vec3Dot(vector, v2.vector); }

public:
	float &x, &y, &z;
	float vector[3];

	const static Vector3 Zero;
};

#define OPERATOR_PARAMETER  const Vector3& first, const Vector3& second
#define OPERATOR_PARAMETER_NUM const Vector3& first, const float num
#define OPERATOR_PARAMETER_UNCONST Vector3& first, const Vector3& second
#define OPERATOR_PARAMETER_NUM_UNCONST Vector3& first, const float num
#define KS_MATH_GET_DEV float xx = first.x - second.x, yy = first.y - second.y, zz = first.z - second.z

inline KS_DLL bool operator == (OPERATOR_PARAMETER)
{
	KS_MATH_GET_DEV;
	return bx::fabsolute(xx) <= KS_MATH_COMPARE_DEV
		&& bx::fabsolute(yy) <= KS_MATH_COMPARE_DEV
		&& bx::fabsolute(zz) <= KS_MATH_COMPARE_DEV;
}

inline KS_DLL bool operator < (OPERATOR_PARAMETER)
{
	KS_MATH_GET_DEV;
	return (xx < -KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy < -KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy <= KS_MATH_COMPARE_DEV && yy >= -KS_MATH_COMPARE_DEV && zz < KS_MATH_COMPARE_DEV);
}

inline KS_DLL bool operator > (OPERATOR_PARAMETER)
{
	KS_MATH_GET_DEV;
	return (xx > KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy > KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy <= KS_MATH_COMPARE_DEV && yy >= -KS_MATH_COMPARE_DEV && zz > KS_MATH_COMPARE_DEV);
}

inline KS_DLL bool operator <= (OPERATOR_PARAMETER)
{
	return (first < second) || (first == second);
}

inline KS_DLL bool operator >= (OPERATOR_PARAMETER)
{
	return (first > second) || (first == second);
}

inline KS_DLL Vector3 operator + (OPERATOR_PARAMETER)
{
	Vector3 vec;
	bx::vec3Add(vec.vector, first.vector, second.vector);
	return vec;
}

inline KS_DLL Vector3 operator + (OPERATOR_PARAMETER_NUM)
{
	Vector3 vec;
	bx::vec3Add(vec.vector, first.vector, num);
	return vec;
}

inline KS_DLL Vector3 operator - (OPERATOR_PARAMETER)
{
	Vector3 vec;
	bx::vec3Sub(vec.vector, first.vector, second.vector);
	return vec;
}

inline KS_DLL Vector3 operator - (OPERATOR_PARAMETER_NUM)
{
	Vector3 vec;
	bx::vec3Sub(vec.vector, first.vector, num);
	return vec;
}

//cross mul
inline KS_DLL Vector3 operator * (const Vector3& first, const Vector3& second)
{
	Vector3 vec;
	bx::vec3Cross(vec.vector, first.vector, second.vector);
	return vec;
}

inline KS_DLL Vector3 operator * (OPERATOR_PARAMETER_NUM)
{
	Vector3 vec;
	bx::vec3Mul(vec.vector, first.vector, num);
	return vec;
}

inline KS_DLL Vector3& operator += (OPERATOR_PARAMETER_UNCONST)
{
	bx::vec3Add(first.vector, first.vector, second.vector);
	return first;
}

inline KS_DLL Vector3& operator += (OPERATOR_PARAMETER_NUM_UNCONST)
{
	bx::vec3Add(first.vector, first.vector, num);
	return first;
}

inline KS_DLL Vector3& operator -= (OPERATOR_PARAMETER_UNCONST)
{
	bx::vec3Sub(first.vector, first.vector, second.vector);
	return first;
}

inline KS_DLL Vector3& operator -= (OPERATOR_PARAMETER_NUM_UNCONST)
{
	bx::vec3Sub(first.vector, first.vector, num);
	return first;
}

//cross mul
inline KS_DLL Vector3& operator *= (Vector3& first, const Vector3& second)
{
	bx::vec3Cross(first.vector, first.vector, second.vector);
	return first;
}

inline KS_DLL Vector3& operator * (OPERATOR_PARAMETER_NUM_UNCONST)
{
	bx::vec3Mul(first.vector, first.vector, num);
	return first;
}

KS_DLL Vector3 operator * (const Vector3& first, const Matrix4x4& second);
KS_DLL Vector3 operator * (const Vector3& first, const Vector4& second);

KS_DLL Vector3& operator *= (Vector3& first, const Matrix4x4& second);
KS_DLL Vector3& operator *= (Vector3& first, const Vector4& second);

#undef OPERATOR_PARAMETER
#undef OPERATOR_PARAMETER_NUM
#undef OPERATOR_PARAMETER_UNCONST
#undef OPERATOR_PARAMETER_NUM_UNCONST
#undef KS_MATH_GET_DEV

KS_MATH_END


#endif