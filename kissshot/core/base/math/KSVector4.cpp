#include "KSVector4.h"
#include "KSVector3.h"
#include "KSMatrix4x4.h"

KS_MATH_BEGIN

const Vector4 Vector4::Zero({ 0.0f,0.0f,0.0f,0.0f });
const Vector4 Vector4::Identity;


Vector4::Vector4(const Vector3 & vec)
	:Vector4()
{
	*this = vec;
}

inline Vector4 & Vector4::operator=(const Vector3 & vec3)
{
	set(vec3.x, vec3.y, vec3.z);
	return *this;
}

Vector4 operator*(const Vector4 & first, const Matrix4x4 & second)
{
	Vector4 vec;
	bx::vec4MulMtx(vec.vector, first.vector, second.matrix);
	return vec;
}

Vector4 & operator*=(Vector4 & first, const Matrix4x4 & second)
{
	bx::vec4MulMtx(first.vector, first.vector, second.matrix);
	return first;
}

KS_MATH_END


