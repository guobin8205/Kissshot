#include "KSVector3.h"
#include "KSVector4.h"
#include "KSMatrix4x4.h"
#include <bx/fpumath.h>

KS_MATH_BEGIN

const Vector3 Vector3::Zero({ 0.0f,0.0f,0.0f });
const Vector3 Vector3::Identity({ 1.0f,1.0f,1.0f });

Vector3::Vector3(void)
	: x(vector[0])
	, y(vector[1])
	, z(vector[2]) 
{ 
	std::memset(vector, 0, sizeof(float) * 3);
}

Vector3::Vector3(const float(&ff)[3]) 
	: Vector3()
{
	bx::vec3Move(vector, ff); 
}

Vector3::Vector3(float xx, float yy, float zz) 
	: Vector3() 
{
	x = xx, y = yy, z = zz;
}

Vector3::Vector3(const Vector3& other) 
	: Vector3() 
{
	*this = other;
}

Vector3& Vector3::normalizing(void)
{
	bx::vec3Norm(vector, vector);
	return *this;
}

Vector3& Vector3::invert(void)
{
	bx::vec3Neg(vector, vector);
	return *this;
}

Vector3& Vector3::absoulte(void)
{
	bx::vec3Abs(vector, vector);
	return *this;
}

Vector3 Vector3::getNormalizing(void)
{
	Vector3 res = *this;
	return res.normalizing();
}

Vector3 Vector3::getInvert(void)
{
	Vector3 res = *this;
	return res.invert();
}

Vector3 Vector3::getAbsoulte(void) const
{
	Vector3 res = *this;
	return res.absoulte();
}

Vector3& Vector3::scale(float xx, float yy, float zz)
{
	x *= xx; y *= yy; z *= zz;
	return *this;
}

Vector3& Vector3::scale(const Vector3& s)
{
	x *= s.x; y *= s.y; z *= s.z;
	return *this;
}

Vector3& Vector3::set(float xx, float yy, float zz)
{
	x = xx; y = yy; z = zz;
	return *this; 
}

float Vector3::length(void) 
{
	return bx::vec3Length(vector);
}

float Vector3::dot(const Vector3& v2)
{
	return bx::vec3Dot(vector, v2.vector);
}

Vector3& Vector3::operator= (const Vector3& other)
{
	x = other.x, y = other.y, z = other.z;
	return *this;
}

inline bool operator == (const Vector3& first, const Vector3& second)
{
	float xx = first.x - second.x, yy = first.y - second.y, zz = first.z - second.z;
	return bx::fabsolute(xx) <= KS_MATH_COMPARE_DEV
		&& bx::fabsolute(yy) <= KS_MATH_COMPARE_DEV
		&& bx::fabsolute(zz) <= KS_MATH_COMPARE_DEV;
}

inline bool operator < (const Vector3& first, const Vector3& second)
{
	float xx = first.x - second.x, yy = first.y - second.y, zz = first.z - second.z;
	return (xx < -KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy < -KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy <= KS_MATH_COMPARE_DEV && yy >= -KS_MATH_COMPARE_DEV && zz < KS_MATH_COMPARE_DEV);
}

inline bool operator > (const Vector3& first, const Vector3& second)
{
	float xx = first.x - second.x, yy = first.y - second.y, zz = first.z - second.z;
	return (xx > KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy > KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy <= KS_MATH_COMPARE_DEV && yy >= -KS_MATH_COMPARE_DEV && zz > KS_MATH_COMPARE_DEV);
}

inline bool operator <= (const Vector3& first, const Vector3& second)
{
	return (first < second) || (first == second);
}

inline bool operator >= (const Vector3& first, const Vector3& second)
{
	return (first > second) || (first == second);
}

inline Vector3 operator + (const Vector3& first, const Vector3& second)
{
	Vector3 vec;
	bx::vec3Add(vec.vector, first.vector, second.vector);
	return vec;
}

inline Vector3 operator + (const Vector3& first, const float num)
{
	Vector3 vec;
	bx::vec3Add(vec.vector, first.vector, num);
	return vec;
}

inline Vector3 operator - (const Vector3& first, const Vector3& second)
{
	Vector3 vec;
	bx::vec3Sub(vec.vector, first.vector, second.vector);
	return vec;
}

inline Vector3 operator - (const Vector3& first, const float num)
{
	Vector3 vec;
	bx::vec3Sub(vec.vector, first.vector, num);
	return vec;
}

//cross mul
inline Vector3 operator * (const Vector3& first, const Vector3& second)
{
	Vector3 vec;
	bx::vec3Cross(vec.vector, first.vector, second.vector);
	return vec;
}

inline Vector3 operator * (const Vector3& first, const float num)
{
	Vector3 vec;
	bx::vec3Mul(vec.vector, first.vector, num);
	return vec;
}

inline Vector3& operator += (Vector3& first, const Vector3& second)
{
	bx::vec3Add(first.vector, first.vector, second.vector);
	return first;
}

inline Vector3& operator += (Vector3& first, const float num)
{
	bx::vec3Add(first.vector, first.vector, num);
	return first;
}

inline Vector3& operator -= (Vector3& first, const Vector3& second)
{
	bx::vec3Sub(first.vector, first.vector, second.vector);
	return first;
}

inline Vector3& operator -= (Vector3& first, const float num)
{
	bx::vec3Sub(first.vector, first.vector, num);
	return first;
}

//cross mul
inline Vector3& operator *= (Vector3& first, const Vector3& second)
{
	bx::vec3Cross(first.vector, first.vector, second.vector);
	return first;
}

inline Vector3& operator *= (Vector3& first, const float num)
{
	bx::vec3Mul(first.vector, first.vector, num);
	return first;
}


inline Vector3 operator*(const Vector3 & first, const Matrix4x4 & second)
{
	Vector3 vec;
	bx::vec3MulMtxH(vec.vector, first.vector, second.matrix);
	return vec;
}

inline Vector3 operator*(const Vector3 & first, const Vector4 & second)
{
	Vector3 vec;
	bx::vec3MulQuat(vec.vector, first.vector, second.vector);
	return vec;
}

inline Vector3 & operator*=(Vector3 & first, const Matrix4x4 & second)
{
	bx::vec3MulMtxH(first.vector, first.vector, second.matrix);
	return first;
}

inline Vector3 & operator*=(Vector3 & first, const Vector4 & second)
{
	bx::vec3MulQuat(first.vector, first.vector, second.vector);
	return first;
}

KS_MATH_END