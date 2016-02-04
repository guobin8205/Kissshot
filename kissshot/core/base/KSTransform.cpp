#include "KSTransform.h"
#include "KSMath.h"

KS_BEGIN

math::Matrix4x4 Transform::getMatrix()
{
	return math::MtxSRT(scale.x, scale.y, scale.z,
			rotate.x, rotate.y, rotate.z,
			position.x, position.y, position.z);
}


KS_END