#pragma once

#ifndef __KISSSHOT__ENGINE__MATH__VECTOR3__
#define __KISSSHOT__ENGINE__MATH__VECTOR3__

#include "KSMathMacro.h"
#include <memory>

KS_MATH_BEGIN

class Matrix4x4;
class Vector4;

class KS_DLL Vector3 final
{
public:
	Vector3(void);
	Vector3(const float(&ff)[3]);
	Vector3(float xx, float yy, float zz);
	Vector3(const Vector3& other);

	///this function will change this;
	///return *this
	inline Vector3& normalizing(void);

	///this function will change this;
	///return *this
	inline Vector3& invert(void);

	///this function will change this;
	///return *this
	inline Vector3& absoulte(void);

	inline Vector3 getNormalizing(void);

	inline Vector3 getInvert(void);

	inline Vector3 getAbsoulte(void) const;

	inline Vector3& scale(float xx, float yy = 1.0f, float zz = 1.0f);

	inline Vector3& scale(const Vector3& s);

	inline Vector3& set(float xx, float yy, float zz);

	inline float length(void);
	inline float dot(const Vector3& v2);
	
	inline Vector3& operator= (const Vector3& other);

public:
	float &x, &y, &z;
	float vector[3];

	const static Vector3 Zero;
	const static Vector3 Identity;
};

extern inline KS_DLL bool operator == (const Vector3& first, const Vector3& second);

extern inline KS_DLL bool operator < (const Vector3& first, const Vector3& second);

extern inline KS_DLL bool operator > (const Vector3& first, const Vector3& second);

extern inline KS_DLL bool operator <= (const Vector3& first, const Vector3& second);

extern inline KS_DLL bool operator >= (const Vector3& first, const Vector3& second);

extern inline KS_DLL Vector3 operator + (const Vector3& first, const Vector3& second);

extern inline KS_DLL Vector3 operator + (const Vector3& first, const float num);

extern inline KS_DLL Vector3 operator - (const Vector3& first, const Vector3& second);

extern inline KS_DLL Vector3 operator - (const Vector3& first, const float num);

//cross mul
extern inline KS_DLL Vector3 operator * (const Vector3& first, const Vector3& second);

extern inline KS_DLL Vector3 operator * (const Vector3& first, const float num);

extern inline KS_DLL Vector3& operator += (Vector3& first, const Vector3& second);

extern inline KS_DLL Vector3& operator += (Vector3& first, const float num);

extern inline KS_DLL Vector3& operator -= (Vector3& first, const Vector3& second);

extern inline KS_DLL Vector3& operator -= (Vector3& first, const float num);

//cross mul
extern inline KS_DLL Vector3& operator *= (Vector3& first, const Vector3& second);

extern inline KS_DLL Vector3& operator *= (Vector3& first, const float num);

extern inline KS_DLL Vector3 operator * (const Vector3& first, const Matrix4x4& second);
extern inline KS_DLL Vector3 operator * (const Vector3& first, const Vector4& second);

extern inline KS_DLL Vector3& operator *= (Vector3& first, const Matrix4x4& second);
extern inline KS_DLL Vector3& operator *= (Vector3& first, const Vector4& second);

KS_MATH_END


#endif