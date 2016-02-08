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
	Vector4(void);
	Vector4(const float(&ff)[4]);
	Vector4(const Vector3 &vec);

	///this function will change this;
	///return *this
	inline Vector4& normalizing(void);

	///this function will change this;
	///return *this
	inline Vector4& invert(void);

	///this function will change this;
	///return *this
	inline Vector4& absoulte(void);

	inline Vector4 getNormalizing(void);

	inline Vector4 getInvert(void);

	inline Vector4 getAbsoulte(void) const;

	inline Vector4& scale(float xx, float yy = 1.0f, float zz = 1.0f, float ww = 1.0f);

	inline Vector4& scale(const Vector4& s);

	inline Vector4& set(float xx, float yy, float zz, float ww = 1.0f);

	//ignore w
	inline float length(void);
	inline float dot(const Vector4& v2);

	inline Vector4& operator=(const Vector3& vec3);

public:
	float &x, &y, &z, &w;
	float vector[4];

	const static Vector4 Zero;
	const static Vector4 Identity;
};


extern inline KS_DLL bool operator == ( const Vector4& first, const Vector4& second);

extern inline KS_DLL bool operator < ( const Vector4& first, const Vector4& second);

extern inline KS_DLL bool operator > ( const Vector4& first, const Vector4& second);

extern inline KS_DLL bool operator <= ( const Vector4& first, const Vector4& second);

extern inline KS_DLL bool operator >= ( const Vector4& first, const Vector4& second);

extern inline KS_DLL Vector4 operator + ( const Vector4& first, const Vector4& second);

extern inline KS_DLL Vector4 operator + (const Vector4& first, const float num);

extern inline KS_DLL Vector4 operator - ( const Vector4& first, const Vector4& second);

extern inline KS_DLL Vector4 operator - (const Vector4& first, const float num);

//cross mul
extern inline KS_DLL Vector4 operator * ( const Vector4& first, const Vector4& second);

extern inline KS_DLL Vector4 operator * (const Vector4& first, const float num);

extern inline KS_DLL Vector4& operator += (Vector4& first, const Vector4& second);

extern inline KS_DLL Vector4& operator += (Vector4& first, const float num);

extern inline KS_DLL Vector4& operator -= (Vector4& first, const Vector4& second);

extern inline KS_DLL Vector4& operator -= (Vector4& first, const float num);

//cross mul
extern inline KS_DLL Vector4& operator *= (Vector4& first, const Vector4& second);

extern inline KS_DLL Vector4& operator *= (Vector4& first, const float num);

extern inline KS_DLL Vector4 operator * (const Vector4& first, const Matrix4x4& second);

extern inline KS_DLL Vector4& operator *= (Vector4& first, const Matrix4x4& second);

KS_MATH_END


#endif