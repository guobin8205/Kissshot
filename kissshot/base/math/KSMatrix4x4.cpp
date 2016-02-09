#include "KSMatrix4x4.h"
#include <bx/fpumath.h>

KS_MATH_BEGIN

const Matrix4x4 Matrix4x4::Zero({
	0.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 0.0f
});
const Matrix4x4 Matrix4x4::Identity;

Matrix4x4::Matrix4x4(void)
{
	bx::mtxIdentity(matrix);
}

Matrix4x4::Matrix4x4(const float(&mtx)[16])
{
	matrix[ 0] = mtx[ 0];
	matrix[ 1] = mtx[ 1];
	matrix[ 2] = mtx[ 2];
	matrix[ 3] = mtx[ 3];
	matrix[ 4] = mtx[ 4];
	matrix[ 5] = mtx[ 5];
	matrix[ 6] = mtx[ 6];
	matrix[ 7] = mtx[ 7];
	matrix[ 8] = mtx[ 8];
	matrix[ 9] = mtx[ 9];
	matrix[10] = mtx[10];
	matrix[11] = mtx[11];
	matrix[12] = mtx[12];
	matrix[13] = mtx[13];
	matrix[14] = mtx[14];
	matrix[15] = mtx[15];
}

Matrix4x4::Matrix4x4(const Matrix4x4 & other)
	: Matrix4x4()
{
	*this = other;
}

Matrix4x4& Matrix4x4::inverse(void)
{
	bx::mtxInverse(matrix, matrix);
	return *this;
}

Matrix4x4 Matrix4x4::getInverse(void) const
{
	Matrix4x4 res(matrix);
	res.inverse();
	return res;
}

inline Matrix4x4 & Matrix4x4::operator=(const Matrix4x4 & other)
{
	auto mtx = other.matrix;
	matrix[ 0] = mtx[ 0];
	matrix[ 1] = mtx[ 1];
	matrix[ 2] = mtx[ 2];
	matrix[ 3] = mtx[ 3];
	matrix[ 4] = mtx[ 4];
	matrix[ 5] = mtx[ 5];
	matrix[ 6] = mtx[ 6];
	matrix[ 7] = mtx[ 7];
	matrix[ 8] = mtx[ 8];
	matrix[ 9] = mtx[ 9];
	matrix[10] = mtx[10];
	matrix[11] = mtx[11];
	matrix[12] = mtx[12];
	matrix[13] = mtx[13];
	matrix[14] = mtx[14];
	matrix[15] = mtx[15];
	return *this;
}

inline Matrix4x4 operator + (const Matrix4x4& first, const Matrix4x4& second)
{
	Matrix4x4 mat;
	auto &res = mat.matrix;
	auto &fm = first.matrix, &sm = second.matrix;
	res[ 0] = fm[ 0] + sm[ 0];
	res[ 1] = fm[ 1] + sm[ 1];
	res[ 2] = fm[ 2] + sm[ 2];
	res[ 3] = fm[ 3] + sm[ 3];
	res[ 4] = fm[ 4] + sm[ 4];
	res[ 5] = fm[ 5] + sm[ 5];
	res[ 6] = fm[ 6] + sm[ 6];
	res[ 7] = fm[ 7] + sm[ 7];
	res[ 8] = fm[ 8] + sm[ 8];
	res[ 9] = fm[ 9] + sm[ 9];
	res[10] = fm[10] + sm[10];
	res[11] = fm[11] + sm[11];
	res[12] = fm[12] + sm[12];
	res[13] = fm[13] + sm[13];
	res[14] = fm[14] + sm[14];
	res[15] = fm[15] + sm[15];
	return mat;
}

inline Matrix4x4 operator * (const Matrix4x4& first, const Matrix4x4& second)
{
	Matrix4x4 mat;
	bx::mtxMul(mat.matrix, first.matrix, second.matrix);
	return mat;
}

inline Matrix4x4 operator * (const Matrix4x4& first, const float& num)
{
	Matrix4x4 mat;
	auto &res = mat.matrix;
	auto &fm = first.matrix;
	res[ 0] = fm[ 0] * num;
	res[ 1] = fm[ 1] * num;
	res[ 2] = fm[ 2] * num;
	res[ 3] = fm[ 3] * num;
	res[ 4] = fm[ 4] * num;
	res[ 5] = fm[ 5] * num;
	res[ 6] = fm[ 6] * num;
	res[ 7] = fm[ 7] * num;
	res[ 8] = fm[ 8] * num;
	res[ 9] = fm[ 9] * num;
	res[10] = fm[10] * num;
	res[11] = fm[11] * num;
	res[12] = fm[12] * num;
	res[13] = fm[13] * num;
	res[14] = fm[14] * num;
	res[15] = fm[15] * num;
	return mat;
}

inline Matrix4x4 operator * (const float& num,const Matrix4x4& first)
{
	Matrix4x4 mat;
	auto &res = mat.matrix;
	auto &fm = first.matrix;
	res[ 0] = fm[ 0] * num;
	res[ 1] = fm[ 1] * num;
	res[ 2] = fm[ 2] * num;
	res[ 3] = fm[ 3] * num;
	res[ 4] = fm[ 4] * num;
	res[ 5] = fm[ 5] * num;
	res[ 6] = fm[ 6] * num;
	res[ 7] = fm[ 7] * num;
	res[ 8] = fm[ 8] * num;
	res[ 9] = fm[ 9] * num;
	res[10] = fm[10] * num;
	res[11] = fm[11] * num;
	res[12] = fm[12] * num;
	res[13] = fm[13] * num;
	res[14] = fm[14] * num;
	res[15] = fm[15] * num;
	return mat;
}

inline Matrix4x4 operator / (const Matrix4x4& first, const Matrix4x4& second)
{
	return first * second.getInverse();
}

inline Matrix4x4 operator / (const Matrix4x4& first, const float& num)
{
	float temp = 1 / num;
	return first * temp;
}

inline Matrix4x4& operator += (Matrix4x4& first, const Matrix4x4& second)
{
	auto &fm = first.matrix;
	auto &sm = second.matrix;
	fm[ 0] = fm[ 0] + sm[ 0];
	fm[ 1] = fm[ 1] + sm[ 1];
	fm[ 2] = fm[ 2] + sm[ 2];
	fm[ 3] = fm[ 3] + sm[ 3];
	fm[ 4] = fm[ 4] + sm[ 4];
	fm[ 5] = fm[ 5] + sm[ 5];
	fm[ 6] = fm[ 6] + sm[ 6];
	fm[ 7] = fm[ 7] + sm[ 7];
	fm[ 8] = fm[ 8] + sm[ 8];
	fm[ 9] = fm[ 9] + sm[ 9];
	fm[10] = fm[10] + sm[10];
	fm[11] = fm[11] + sm[11];
	fm[12] = fm[12] + sm[12];
	fm[13] = fm[13] + sm[13];
	fm[14] = fm[14] + sm[14];
	fm[15] = fm[15] + sm[15];
	return first;
}

inline Matrix4x4 operator *= (Matrix4x4& first, const Matrix4x4& second)
{
	bx::mtxMul(first.matrix, first.matrix, second.matrix);
	return first;
}

inline Matrix4x4 operator *= (Matrix4x4& first, const float& num)
{
	auto &fm = first.matrix;
	fm[ 0] = fm[ 0] * num;
	fm[ 1] = fm[ 1] * num;
	fm[ 2] = fm[ 2] * num;
	fm[ 3] = fm[ 3] * num;
	fm[ 4] = fm[ 4] * num;
	fm[ 5] = fm[ 5] * num;
	fm[ 6] = fm[ 6] * num;
	fm[ 7] = fm[ 7] * num;
	fm[ 8] = fm[ 8] * num;
	fm[ 9] = fm[ 9] * num;
	fm[10] = fm[10] * num;
	fm[11] = fm[11] * num;
	fm[12] = fm[12] * num;
	fm[13] = fm[13] * num;
	fm[14] = fm[14] * num;
	fm[15] = fm[15] * num;
	return first;
}

inline Matrix4x4 operator /= (Matrix4x4& first, const Matrix4x4& second)
{
	return first *= second.getInverse();
}

inline Matrix4x4& operator /= (Matrix4x4& first, const float& num)
{
	float temp = 1 / num;
	first *= temp;
	return first;
}

inline Matrix4x4 MtxxTranslate(float xx, float yy, float zz)
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

inline Matrix4x4 MtxRotateX(float rotation)
{
	Matrix4x4 res;
	bx::mtxRotateX(res.matrix, bx::toRad(rotation));
	return res;
}


inline Matrix4x4 MtxRotateY(float rotation)
{
	Matrix4x4 res;
	bx::mtxRotateY(res.matrix, bx::toRad(rotation));
	return res;
}

inline Matrix4x4 MtxRotateZ(float rotation)
{
	Matrix4x4 res;
	bx::mtxRotateZ(res.matrix, bx::toRad(rotation));
	return res;
}

inline Matrix4x4 MtxRotateXYZ(float ax, float ay, float az)
{
	Matrix4x4 res;
	bx::mtxRotateXYZ(res.matrix, bx::toRad(ax), bx::toRad(ay), bx::toRad(az));
	return res;
}

inline Matrix4x4 MtxSRT(float sx, float sy, float sz, float rx, float ry, float rz, float tx, float ty, float tz)
{
	Matrix4x4 res;
	bx::mtxSRT(res.matrix, sx, sy, sz, bx::toRad(rx), bx::toRad(ry), bx::toRad(rz), tx, ty, tz);
	return res;
}

inline Matrix4x4 MtxOrtho(float _left, float _right, float _bottom, float _top, float _near, float _far, float _offset, bool _oglNdc)
{
	Matrix4x4 res;
	bx::mtxOrtho(res.matrix, _left, _right, _bottom, _top, _near, _far, _offset, _oglNdc);
	return res;
}

inline Matrix4x4 MtxOrtho(float _width, float _height, float _near, float _far, float _offset, bool _oglNdc)
{
	Matrix4x4 res;
	bx::mtxOrtho(res.matrix, 0.0f, _width, 0.0f, _height, _near, _far, _offset, _oglNdc);
	return res;
}

inline KS_DLL Matrix4x4 MtxProj(float _fovy, float _aspect, float _near, float _far, bool _orgNdc)
{
	Matrix4x4 result;
	bx::mtxProj(result.matrix, _fovy, _aspect, _near, _far, _orgNdc);
	return result;
}

KS_MATH_END