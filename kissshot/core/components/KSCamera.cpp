#include "KSCamera.h"
#include <bx/fpumath.h>
#include <bgfx/bgfx.h>

#include "container/KSEntity.h"

KS_USE_MATH;
KS_USE_COMPONENT;

#define DEFAULT_CAMERA_ID ((uint8_t)0)

static std::shared_ptr<Camera> mCamara;

Camera::Camera(const CameraType & type)
	: mType(type)
	, mLookAt(0.0f,0.0f,0.0f)
	, mUp(0.0f,1.0f,0.0f)
	, mSize(800.0f,480.0f)
	, mNear(0.1f)
	, mFar(100.0f)
{
}

Matrix4x4 Camera::getViewMatrix(void)
{
	Matrix4x4 result = Matrix4x4::Identity;
	switch (mType)
	{
	case ::kissshot::core::component::Camera::CameraType::Orthogonal:
		result = _getOrthognalMatrix();
		break;
	case ::kissshot::core::component::Camera::CameraType::Perspective:
		result = _getPerspectiveMatrix();
		break;
	default:
		break;
	}
	return result;
}

void Camera::use(uint8_t id)
{
	mCamara = this->shared_from_this();
	switch (mType)
	{
	case ::kissshot::core::component::Camera::CameraType::Orthogonal:
		_useOrthMatrix(id);
		break;
	case ::kissshot::core::component::Camera::CameraType::Perspective:
		_usePresMatrix(id);
		break;
	default:
		break;
	}
}

Matrix4x4 Camera::_getOrthognalMatrix(void)
{
	auto owner = getOwner();
	if (!owner) return Matrix4x4::Identity;

	auto& trans = owner->transform();
	auto proj = MtxOrtho(mSize.width, mSize.height, mNear, mFar);
	Matrix4x4 lookat;
	Vector3 pos = trans.position;
	pos.x -= mSize.width * 0.5f, pos.y -= mSize.height * 0.5f;
	mLookAt.x = pos.x, mLookAt.y = pos.y;
	bx::mtxLookAt(lookat.matrix, trans.position.vector, mLookAt.vector, mUp.vector);

	return lookat * proj;
}

Matrix4x4 Camera::_getPerspectiveMatrix(void)
{
	auto owner = getOwner();
	if (!owner) return Matrix4x4::Identity;

	auto& trans = owner->transform();
	auto proj = MtxProj(mFovy, mSize.width / mSize.height, mNear, mFar);
	Matrix4x4 lookat;
	bx::mtxLookAt(lookat.matrix, trans.position.vector, mLookAt.vector, mUp.vector);

	return lookat * proj;
}

void Camera::_useOrthMatrix(uint8_t id)
{
	auto owner = getOwner();
	if (!owner) return;

	auto& trans = owner->transform();
	auto proj = MtxOrtho(mSize.width,mSize.height, mNear, mFar);
	Matrix4x4 lookat;
	Vector3 pos = trans.position;
	pos.x -= mSize.width * 0.5f, pos.y -= mSize.height * 0.5f;
	mLookAt.x = pos.x, mLookAt.y = pos.y;
	bx::mtxLookAt(lookat.matrix, pos.vector, mLookAt.vector, mUp.vector);

	bgfx::setViewTransform(id, lookat.matrix, proj.matrix);
}

void Camera::_usePresMatrix(uint8_t id)
{
	auto owner = getOwner();
	if (!owner) return;

	auto& trans = owner->transform();
	auto proj = MtxProj(mFovy, mSize.width / mSize.height, mNear, mFar,true);
	Matrix4x4 lookat;
	bx::mtxLookAt(lookat.matrix, trans.position.vector, mLookAt.vector, mUp.vector);

	bgfx::setViewTransform(id, lookat.matrix, proj.matrix);
}
