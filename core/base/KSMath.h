#pragma once
#ifndef __KISSSHOT__ENGINE__MATH__
#define __KISSSHOT__ENGINE__MATH__

#include "KSMacro.h"
#include <math.h>
#include <bx/fpumath.h>
#include <memory>
KS_BEGIN

class KS_DLL Matrix4x4 final
{
public:
	Matrix4x4(void) { std::memset(mMatrix, 0, sizeof(float) * 16); }
	Matrix4x4(const float(&ff)[16]) { std::memcpy(mMatrix, ff, sizeof(float) * 16); }

	inline Matrix4x4 inverse(void)
	{
		bx::mtxInverse(mMatrix, mMatrix);
		return *this;
	}

	//float& operator [] (uint32 index) { return mMatrix[index]; }
	inline operator float* () { return mMatrix; }
	inline operator const float* () { return mMatrix; }
	inline operator const float* () const { return mMatrix; }
	inline Matrix4x4& operator = (const float(&ff)[16]) { std::memcpy(mMatrix, ff, sizeof(float) * 16); return  *this; }

	inline Matrix4x4 operator*(const Matrix4x4& second)
	{
		Matrix4x4 res;
		bx::mtxMul(res, mMatrix, second);
		return res;
	}
private:
	float mMatrix[16];
};

class KS_DLL Vector3 final
{
public:
	Vector3(void) { std::memset(mVector, 0, sizeof(float) * 3); }
	Vector3(const float(&ff)[3]) { bx::vec3Move(mVector, ff); }
	inline Vector3& normalizing(void)
	{
		bx::vec3Norm(mVector, mVector);
		return *this;
	}

	inline Vector3& invert(void)
	{
		bx::vec3Neg(mVector, mVector);
		return *this;
	}

	inline float length(void) { return bx::vec3Length(mVector); }
	inline float dot(const Vector3& v2) { return bx::vec3Dot(mVector, v2); }

	inline operator float* () { return mVector; }
	inline operator const float* () const { return mVector; }
	inline Vector3& operator = (const float(&ff)[3]) { bx::vec3Move(mVector, ff); return  *this; }

	inline Vector3 operator *(const Matrix4x4& second)
	{
		Vector3 res;
		bx::vec3MulMtx(res, mVector, second);
		return res;
	}

	inline Vector3 operator+(const Vector3& second)
	{
		Vector3 res;
		bx::vec3Add(res, mVector, second);
		return res;
	}
	inline Vector3 operator+(const float& second)
	{
		Vector3 res;
		bx::vec3Add(res, mVector, second);
		return res;
	}
	inline Vector3 operator-(const Vector3& second)
	{
		Vector3 res;
		bx::vec3Sub(res, mVector, second);
		return res;
	}
	inline Vector3 operator-(const float& second)
	{
		Vector3 res;
		bx::vec3Sub(res, mVector, second);
		return res;
	}
	inline Vector3 operator*(const float& second)
	{
		Vector3 res;
		bx::vec3Mul(res, mVector, second);
		return res;
	}
	//cross mul
	inline Vector3 operator*(const Vector3& second)
	{
		Vector3 res;
		bx::vec3Cross(res, mVector, second);
		return res;
	}

private:
	float mVector[3];
};

class KS_DLL Vector4 final
{
public:
	Vector4(void) { std::memset(mVector, 0, sizeof(float) * 4); }
	Vector4(const float(&ff)[4]) {}
private:
	float mVector[4];
};


inline Matrix4x4 MtxTransform(float xx, float yy, float zz)
{
	Matrix4x4 res;
	bx::mtxTranslate(res, xx, yy, zz);
	return res;

}

inline Matrix4x4 MtxScale(float xx, float yy, float zz)
{
	Matrix4x4 res;
	bx::mtxScale(res, xx, yy, zz);
	return res;
}

//rotation is 0 to 360
inline Matrix4x4 MtxRotateX(float rotation)
{
	Matrix4x4 res;
	bx::mtxRotateX(res, bx::toDeg(rotation));
	return res;
}

//rotation is 0 to 360
inline Matrix4x4 MtxRotateY(float rotation)
{
	Matrix4x4 res;
	bx::mtxRotateY(res, bx::toDeg(rotation));
	return res;
}

//rotation is 0 to 360
inline Matrix4x4 MtxRotateZ(float rotation)
{
	Matrix4x4 res;
	bx::mtxRotateZ(res, bx::toDeg(rotation));
	return res;
}

//rotation is 0 to 360
inline Matrix4x4 MtxRotateXYZ(float ax, float ay,float az)
{
	Matrix4x4 res;
	bx::mtxRotateXYZ(res, bx::toDeg(ax), bx::toDeg(ay), bx::toDeg(az));
	return res;
}

//rotation is 0 to 360
inline Matrix4x4 MtxSRT(float sx,float sy,float sz,float rx,float ry,float rz,float tx,float ty,float tz)
{
	Matrix4x4 res;
	bx::mtxSRT(res, sx, sy, sz, bx::toDeg(rx), bx::toDeg(ry), bx::toDeg(rz), tx, ty, tz);
	return res;
}

KS_END

#endif