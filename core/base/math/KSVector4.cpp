#include "KSVector4.h"
#include "KSVector3.h"

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


KS_MATH_END