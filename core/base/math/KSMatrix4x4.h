#pragma once

#ifndef __KISSSHOT__ENGINE__MATH__MATRIX4X4__
#define __KISSSHOT__ENGINE__MATH__MATRIX4X4__
#include "KSMathMacro.h"
#include "KSMacro.h"
#include <bx/fpumath.h>
#include <memory>

KS_MATH_BEGIN

class KS_DLL Matrix4x4 final
{
public:
	Matrix4x4(void) { std::memset(matrix, 0, sizeof(float) * 16); }
	Matrix4x4(const float(&ff)[16]) { bx::mtxTranspose(matrix, ff); }

	inline Matrix4x4 inverse(void)
	{
		bx::mtxInverse(matrix, matrix);
		return *this;
	}

public:
	float matrix[16];
};

inline Matrix4x4 MtxTransform(float xx, float yy, float zz)
{
	Matrix4x4 res;
	bx::mtxTranslate(res.matrix, xx, yy, zz);
	return res;

}

inline Matrix4x4 MtxScale(float xx, float yy, float zz)
{
	Matrix4x4 res;
	bx::mtxScale(res.matrix, xx, yy, zz);
	return res;
}

//rotation is 0 to 360
inline Matrix4x4 MtxRotateX(float rotation)
{
	Matrix4x4 res;
	bx::mtxRotateX(res.matrix, bx::toDeg(rotation));
	return res;
}

//rotation is 0 to 360
inline Matrix4x4 MtxRotateY(float rotation)
{
	Matrix4x4 res;
	bx::mtxRotateY(res.matrix, bx::toDeg(rotation));
	return res;
}

//rotation is 0 to 360
inline Matrix4x4 MtxRotateZ(float rotation)
{
	Matrix4x4 res;
	bx::mtxRotateZ(res.matrix, bx::toDeg(rotation));
	return res;
}

//rotation is 0 to 360
inline Matrix4x4 MtxRotateXYZ(float ax, float ay, float az)
{
	Matrix4x4 res;
	bx::mtxRotateXYZ(res.matrix, bx::toDeg(ax), bx::toDeg(ay), bx::toDeg(az));
	return res;
}

//rotation is 0 to 360
inline Matrix4x4 MtxSRT(float sx, float sy, float sz, float rx, float ry, float rz, float tx, float ty, float tz)
{
	Matrix4x4 res;
	bx::mtxSRT(res.matrix, sx, sy, sz, bx::toDeg(rx), bx::toDeg(ry), bx::toDeg(rz), tx, ty, tz);
	return res;
}


KS_MATH_END


#endif