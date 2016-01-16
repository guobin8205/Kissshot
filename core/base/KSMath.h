#pragma once
#ifndef __KISSSHOT__ENGINE__MATH__
#define __KISSSHOT__ENGINE__MATH__

#include "KSMacro.h"
#include <math.h>

KS_BEGIN

class KS_DLL Float3 final
{
public:
	const float& operator[](uint32 index) const { return mFloat[index]; }
	float& operator[](uint32 index) { return mFloat[index]; }
private:
	float mFloat[3];
};

class KS_DLL Float4 final
{
public:
	const float& operator[](uint32 index) const { return mFloat[index]; }
	float& operator[](uint32 index) { return mFloat[index]; }
private:
	float mFloat[4];
};

class KS_DLL Matrix3x3 final
{
public:
	const Float3& operator[](uint32 index) const { return mMatrix[index]; }
	Float3& operator[](uint32 index) { return mMatrix[index]; }
private:
	Float3 mMatrix[3];
};

class KS_DLL Matrix4x4 final
{
public:
	const Float4& operator[](uint32 index) const { return mMatrix[index]; }
	Float4& operator[](uint32 index) { return mMatrix[index]; }
private:
	Float4 mMatrix[4];
};

#define Matrix3x3MulOne(row,cul) res[row][cul] = m1[row][0] * m2[0][cul] + m1[row][1] * m2[1][cul] + m1[row][2] * m2[2][cul]
Matrix3x3 operator *(const Matrix3x3& m1, const Matrix3x3& m2)
{
	Matrix3x3 res;
	Matrix3x3MulOne(0, 0); Matrix3x3MulOne(1, 0); Matrix3x3MulOne(2, 0);
	Matrix3x3MulOne(0, 1); Matrix3x3MulOne(1, 1); Matrix3x3MulOne(2, 1);
	Matrix3x3MulOne(0, 2); Matrix3x3MulOne(1, 2); Matrix3x3MulOne(2, 2);
	return res;
}
#undef Matrix3x3MulOne

#define Matrix4x4MulOne(row,cul) res[row][cul] = m1[row][0] * m2[0][cul] + m1[row][1] * m2[1][cul] + m1[row][2] * m2[2][cul] + m1[row][3] * m2[3][cul]
Matrix4x4 operator *(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 res;
	Matrix4x4MulOne(0, 0); Matrix4x4MulOne(1, 0); Matrix4x4MulOne(2, 0); Matrix4x4MulOne(3, 0);
	Matrix4x4MulOne(0, 1); Matrix4x4MulOne(1, 1); Matrix4x4MulOne(2, 1); Matrix4x4MulOne(3, 1);
	Matrix4x4MulOne(0, 2); Matrix4x4MulOne(1, 2); Matrix4x4MulOne(2, 2); Matrix4x4MulOne(3, 2);
	Matrix4x4MulOne(0, 3); Matrix4x4MulOne(1, 3); Matrix4x4MulOne(2, 3); Matrix4x4MulOne(3, 3);
	return res;
}
#undef Matrix4x4MulOne

#define Matrix3x3FlotMulOne(cul) res[cul] = m1[0] * m2[0][cul] + m1[1] * m2[1][cul] + m1[2] * m2[2][cul]
Float3 operator *(const Float3& m1, const Matrix3x3& m2)
{
	Float3 res;
	Matrix3x3FlotMulOne(0); Matrix3x3FlotMulOne(1); Matrix3x3FlotMulOne(2);
	return res;
}
#undef Matrix4x4FlotMulOne

#define Matrix4x4FlotMulOne(cul) res[cul] = m1[0] * m2[0][cul] + m1[1] * m2[1][cul] + m1[2] * m2[2][cul] + m1[3] * m2[3][cul]
Float4 operator *(const Float4& m1, const Matrix4x4& m2)
{
	Float4 res;
	Matrix4x4FlotMulOne(0); Matrix4x4FlotMulOne(1); Matrix4x4FlotMulOne(2); Matrix4x4FlotMulOne(3);
	return res;
}
#undef Matrix4x4FlotMulOne

//ignore Float4[3]
inline float dot(const Float4& f1, const Float4& f2)
{
	return f1[0] * f2[0] + f1[1] * f2[1] + f1[2] * f2[2];
}

inline float dot(const Float4& f1, const Float4& f2)
{
	return f1[0] * f2[0] + f1[1] * f2[1] + f1[2] * f2[2];
}

inline Matrix4x4 MatrixTransform(float xx, float yy, float zz)
{
	Matrix4x4 res;
	res[3][0] = xx; res[3][1] = yy; res[3][2] = zz; res[3][3] = 1.0f;
	return res;
}

inline Matrix4x4 MatrixRotation(float xx, float yy, float zz)
{

}

KS_END

#endif