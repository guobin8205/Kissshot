#include "KSTransform.h"
#include "KSMath.h"

KS_USE_MATH;

KS_BASE_BEGIN

Transform::Transform()
	: Transform(Vector3::Zero,Vector3::Identity, Vector3::Zero)
{
}


Transform::Transform(const math::Vector3& p, const math::Vector3& s, const math::Vector3& r)
	: position(p)
	, scale(s)
	, rotate(r)
{
}

math::Matrix4x4 Transform::getMatrix()
{
	return MtxSRT(scale.x, scale.y, scale.z,
			rotate.x, rotate.y, rotate.z,
			position.x, position.y, position.z);
}


KS_BASE_END