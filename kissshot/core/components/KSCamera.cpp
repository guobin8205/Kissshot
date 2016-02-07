#include "KSCamera.h"
#include <bx/fpumath.h>
#include <bgfx/bgfx.h>

#include "container/KSEntity.h"

KS_USE_MATH;
KS_USE_COMPONENT;

KSComponentCtorDef(Camera, const CameraType& type)
	: IComponent(owner)
	, mLookAt(0.0f, 0.0f, 0.0f)
	, mUp(0.0f, 1.0f, 0.0f)
	, mType(type)
{
}

KS_MATH::Matrix4x4 Camera::getViewMatrix(void)
{
	auto& owner = getOwner();
	auto& trans = owner.transform();

	switch (mType)
	{
	case ::kissshot::core::component::Camera::CameraType::Orthogonal:
		break;
	case ::kissshot::core::component::Camera::CameraType::Perspective:
		break;
	default:
		break;
	}
	return trans.getMatrix();
}