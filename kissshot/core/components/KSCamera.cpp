#include "KSCamera.h"
#include <bx/fpumath.h>
#include <bgfx/bgfx.h>
KS_COMPONENT_BEGIN

KS_MATH::Matrix4x4 Camera::getViewMatrix(void)
{
	return KS_MATH::Matrix4x4();
}
KS_COMPONENT_END