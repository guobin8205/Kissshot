#include "KSTransform.h"
#include "KSMath.h"

KS_BEGIN

Matrix4x4 Transform::getMatrix()
{
	return MtxSRT(scale[0], scale[1], scale[2],
			rotate[0], rotate[1], rotate[2],
			position[0], position[1], position[2]);
}


KS_END