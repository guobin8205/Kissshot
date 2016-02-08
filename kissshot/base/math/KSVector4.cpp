#include "KSVector4.h"
#include "KSVector3.h"
#include "KSMatrix4x4.h"
#include <bx/fpumath.h>

KS_MATH_BEGIN

const Vector4 Vector4::Zero({ 0.0f,0.0f,0.0f,0.0f });
const Vector4 Vector4::Identity;

Vector4::Vector4(void)
	: x(vector[0]), y(vector[1]), z(vector[2]), w(vector[3])
{
	bx::quatIdentity(vector);
}
Vector4::Vector4(const float(&ff)[4])
	: Vector4()
{
	bx::quatMove(vector, ff);
}

Vector4::Vector4(const Vector3 & vec)
	:Vector4()
{
	*this = vec;
}


Vector4& Vector4::normalizing(void)
{
	bx::quatNorm(vector, vector);
	return *this;
}


Vector4& Vector4::invert(void)
{
	bx::quatInvert(vector, vector);
	return *this;
}


Vector4& Vector4::absoulte(void)
{
	x = bx::fabsolute(x); y = bx::fabsolute(y); z = bx::fabsolute(z); w = bx::fabsolute(w);
	return *this;
}

Vector4 Vector4::getNormalizing(void)
{
	Vector4 res = *this;
	return res.normalizing();
}

Vector4 Vector4::getInvert(void)
{
	Vector4 res = *this;
	return res.invert();
}

Vector4 Vector4::getAbsoulte(void) const
{
	Vector4 res = *this;
	return res.absoulte();
}

Vector4& Vector4::scale(float xx, float yy, float zz, float ww)
{
	x *= xx; y *= yy; z *= zz; w *= ww;
	return *this;
}

Vector4& Vector4::scale(const Vector4& s)
{
	return scale(s.x, s.y, s.z, s.w);
}

Vector4& Vector4::set(float xx, float yy, float zz, float ww)
{ 
	x = xx; y = yy; z = zz; w = ww; 
	return *this; 
}


float Vector4::length(void)
{
	return bx::vec3Length(vector);
}

float Vector4::dot(const Vector4& v2)
{
	return bx::quatDot(vector, v2.vector); 
}

inline Vector4 & Vector4::operator=(const Vector3 & vec3)
{
	set(vec3.x, vec3.y, vec3.z);
	return *this;
}

inline bool operator == (const Vector4& first, const Vector4& second)
{
	float xx = first.x - second.x, yy = first.y - second.y, zz = first.z - second.z, ww = first.w - second.w;
	return bx::fabsolute(xx) <= KS_MATH_COMPARE_DEV
		&& bx::fabsolute(yy) <= KS_MATH_COMPARE_DEV
		&& bx::fabsolute(zz) <= KS_MATH_COMPARE_DEV
		&& bx::fabsolute(ww) <= KS_MATH_COMPARE_DEV;
}

inline bool operator < (const Vector4& first, const Vector4& second)
{
	float xx = first.x - second.x, yy = first.y - second.y, zz = first.z - second.z, ww = first.w - second.w;
	return (xx < -KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy < -KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy <= KS_MATH_COMPARE_DEV && yy >= -KS_MATH_COMPARE_DEV && zz < KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy <= KS_MATH_COMPARE_DEV && yy >= -KS_MATH_COMPARE_DEV && zz <= KS_MATH_COMPARE_DEV && zz >= -KS_MATH_COMPARE_DEV && ww < -KS_MATH_COMPARE_DEV);
}

inline bool operator > (const Vector4& first, const Vector4& second)
{
	float xx = first.x - second.x, yy = first.y - second.y, zz = first.z - second.z, ww = first.w - second.w;
	return (xx > KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy > KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy <= KS_MATH_COMPARE_DEV && yy >= -KS_MATH_COMPARE_DEV && zz > KS_MATH_COMPARE_DEV)
		|| (xx <= KS_MATH_COMPARE_DEV && xx >= -KS_MATH_COMPARE_DEV && yy <= KS_MATH_COMPARE_DEV && yy >= -KS_MATH_COMPARE_DEV && zz <= KS_MATH_COMPARE_DEV && zz >= -KS_MATH_COMPARE_DEV && ww > KS_MATH_COMPARE_DEV);;
}

inline bool operator <= (const Vector4& first, const Vector4& second)
{
	return (first < second) || (first == second);
}

inline bool operator >= (const Vector4& first, const Vector4& second)
{
	return (first > second) || (first == second);
}

inline Vector4 operator + (const Vector4& first, const Vector4& second)
{
	Vector4 vec;
	vec.x = first.x + second.x;
	vec.y = first.y + second.x;
	vec.z = first.z + second.x;
	vec.w = first.w + second.x;
	return vec;
}

inline Vector4 operator + (const Vector4& first, const float num)
{
	Vector4 vec;
	vec.x = first.x + num;
	vec.y = first.y + num;
	vec.z = first.z + num;
	vec.w = first.w + num;
	return vec;
}

inline Vector4 operator - (const Vector4& first, const Vector4& second)
{
	Vector4 vec;
	vec.x = first.x - second.x;
	vec.y = first.y - second.x;
	vec.z = first.z - second.x;
	vec.w = first.w - second.x;
	return vec;
}

inline Vector4 operator - (const Vector4& first, const float num)
{
	Vector4 vec;
	vec.x = first.x - num;
	vec.y = first.y - num;
	vec.z = first.z - num;
	vec.w = first.w - num;
	return vec;
}


inline Vector4 operator * (const Vector4& first, const Vector4& second)
{
	Vector4 vec;
	bx::quatMul(vec.vector, first.vector, second.vector);
	return vec;
}

inline Vector4 operator * (const Vector4& first, const float num)
{
	Vector4 vec;
	vec.x = first.x * num;
	vec.y = first.y * num;
	vec.z = first.z * num;
	vec.w = first.w * num;
	return vec;
}

inline Vector4& operator += (Vector4& first, const Vector4& second)
{
	first.x = first.x + second.x;
	first.y = first.y + second.x;
	first.z = first.z + second.x;
	first.w = first.w + second.x;
	return first;
}

inline Vector4& operator += (Vector4& first, const float num)
{
	first.x = first.x + num;
	first.y = first.y + num;
	first.z = first.z + num;
	first.w = first.w + num;
	return first;
}

inline Vector4& operator -= (Vector4& first, const Vector4& second)
{
	first.x = first.x - second.x;
	first.y = first.y - second.x;
	first.z = first.z - second.x;
	first.w = first.w - second.x;
	return first;
}

inline Vector4& operator -= (Vector4& first, const float num)
{
	first.x = first.x - num;
	first.y = first.y - num;
	first.z = first.z - num;
	first.w = first.w - num;
	return first;
}


inline Vector4& operator *= (Vector4& first, const Vector4& second)
{
	bx::quatMul(first.vector, first.vector, second.vector);
	return first;
}

inline Vector4& operator *= (Vector4& first, const float num)
{
	first.x = first.x * num;
	first.y = first.y * num;
	first.z = first.z * num;
	first.w = first.w * num;
	return first;
}

inline Vector4 operator*(const Vector4 & first, const Matrix4x4 & second)
{
	Vector4 vec;
	bx::vec4MulMtx(vec.vector, first.vector, second.matrix);
	return vec;
}

inline Vector4 & operator*=(Vector4 & first, const Matrix4x4 & second)
{
	bx::vec4MulMtx(first.vector, first.vector, second.matrix);
	return first;
}

KS_MATH_END


