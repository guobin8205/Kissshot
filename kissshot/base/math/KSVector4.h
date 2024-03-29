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
	Vector4& normalizing(void);

	///this function will change this;
	///return *this
	Vector4& invert(void);

	///this function will change this;
	///return *this
	Vector4& absoulte(void);

	Vector4 getNormalizing(void);

	Vector4 getInvert(void);

	Vector4 getAbsoulte(void) const;

	Vector4& scale(float xx, float yy = 1.0f, float zz = 1.0f, float ww = 1.0f);

	Vector4& scale(const Vector4& s);

	Vector4& set(float xx, float yy, float zz, float ww = 1.0f);

	//ignore w
	float length(void);
	float dot(const Vector4& v2);

	Vector4& operator=(const Vector3& vec3);

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