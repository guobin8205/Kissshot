#include "KSVector3.h"
#include "KSMatrix4x4.h"
#include "KSVector4.h"

KS_MATH_BEGIN

const Vector3 Vector3::Zero({ 0.0f,0.0f,0.0f });

Vector3 operator*(const Vector3 & first, const Matrix4x4 & second)
{
	Vector3 vec;
	bx::vec3MulMtxH(vec.vector, first.vector, second.matrix);
	return vec;
}

Vector3 operator*(const Vector3 & first, const Vector4 & second)
{
	Vector3 vec;
	bx::vec3MulQuat(vec.vector, first.vector, second.vector);
	return vec;
}

Vector3 & operator*=(Vector3 & first, const Matrix4x4 & second)
{
	bx::vec3MulMtxH(first.vector, first.vector, second.matrix);
	return first;
}

Vector3 & operator*=(Vector3 & first, const Vector4 & second)
{
	bx::vec3MulQuat(first.vector, first.vector, second.vector);
	return first;
}

KS_MATH_END