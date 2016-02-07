#pragma once

#ifndef __KISSSHOT__ENGINE__MATH__MATRIX4X4__
#define __KISSSHOT__ENGINE__MATH__MATRIX4X4__
#include "KSMathMacro.h"
#include <memory>

KS_MATH_BEGIN

class KS_DLL Matrix4x4 final
{
public:
	Matrix4x4(void) { bx::mtxIdentity(matrix); }
	Matrix4x4(const float(&ff)[16]) { bx::mtxTranspose(matrix, ff); }

	inline Matrix4x4& inverse(void)
	{
		bx::mtxInverse(matrix, matrix);
		return *this;
	}

	inline Matrix4x4 getInverse(void) const
	{
		Matrix4x4 res(matrix);
		res.inverse();
		return res;
	}

public:
	float matrix[16];

	const static Matrix4x4 Zero;
	const static Matrix4x4 Identity;
};


extern inline Matrix4x4 operator + (const Matrix4x4& first, const Matrix4x4& second);

extern inline Matrix4x4 operator * (const Matrix4x4& first, const Matrix4x4& second);

extern inline Matrix4x4 operator * (const Matrix4x4& first, const float& num);

extern inline Matrix4x4 operator * (const float& num, const Matrix4x4& first);

extern inline Matrix4x4 operator / (const Matrix4x4& first, const Matrix4x4& second);

extern inline Matrix4x4 operator / (const Matrix4x4& first, const float& num);

extern inline Matrix4x4& operator += (Matrix4x4& first, const Matrix4x4& second);

extern inline Matrix4x4 operator *= (Matrix4x4& first, const Matrix4x4& second);

extern inline Matrix4x4 operator *= (Matrix4x4& first, const float& num);

extern inline Matrix4x4 operator /= (Matrix4x4& first, const Matrix4x4& second);

extern inline Matrix4x4& operator /= (Matrix4x4& first, const float& num);

extern inline Matrix4x4 MtxxTranslate(float xx, float yy, float zz);

extern inline Matrix4x4 MtxScale(float xx, float yy, float zz);

//rotation is 0 to 360
extern inline Matrix4x4 MtxRotateX(float rotation);

//rotation is 0 to 360
extern inline Matrix4x4 MtxRotateY(float rotation);

//rotation is 0 to 360
extern inline Matrix4x4 MtxRotateZ(float rotation);

//rotation is 0 to 360
extern inline Matrix4x4 MtxRotateXYZ(float ax, float ay, float az);

//rotation is 0 to 360
extern inline Matrix4x4 MtxSRT(float sx, float sy, float sz, float rx, float ry, float rz, float tx, float ty, float tz);

extern inline Matrix4x4 MtxOrtho(float _left, float _right, float _bottom, float _top, float _near, float _far, float _offset = 0.0f, bool _center = false);
extern inline Matrix4x4 MtxOrtho(float _width, float _height, float _near, float _far, float _offset = 0.0f, bool _center = false);

KS_MATH_END


#endif