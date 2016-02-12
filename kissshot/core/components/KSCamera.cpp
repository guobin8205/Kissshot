#include "KSCamera.h"
#include <bx/fpumath.h>
#include <bgfx/bgfx.h>
#include <vector>
#include "container/KSEntity.h"
#include <algorithm>
#include "KSDebug.h"
KS_USE_MATH;
KS_USE_COMPONENT;

#define DEFAULT_CAMERA_ID (0ui8)

static std::vector<CameraRef> CameraList;

static inline bool CameraIdLess(CameraRef first, CameraRef second)
{
	return first->mId < second->mId;
}

Camera::Camera(const CameraType & type, float _near, float _far, float _fovy)
	: mType(type)
	, mLookAt(0.0f, 0.0f, 0.0f)
	, mUp(0.0f, 1.0f, 0.0f)
	, mSize(800.0f, 480.0f)
	, mNear(_near)
	, mFar(_far)
	, mFovy(_fovy)
{
	//find unuse id
	uint8_t id = 0ui8;

	for (auto item : CameraList)
	{
		if (item->mId > id)
			break;
		++id;
	}
	mId = id;
	KSBREAK(mId > sizeof(uint32));
}

Camera::~Camera(void)
{
}

void Camera::setClearCamera(uint16_t flags, uint32_t rgba, float depth, uint8_t stencil)
{
	bgfx::setViewClear(mId, flags, rgba, depth, stencil);
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

void Camera::use(void)
{
	switch (mType)
	{
	case ::kissshot::core::component::Camera::CameraType::Orthogonal:
		_useOrthMatrix();
		break;
	case ::kissshot::core::component::Camera::CameraType::Perspective:
		_usePresMatrix();
		break;
	default:
		break;
	}
}

void Camera::destoryInEntity(void)
{
	IComponent::destoryInEntity();
	auto find = std::find(CameraList.begin(), CameraList.end(), this->shared_from_this());
	if (find != CameraList.end())
		CameraList.erase(find);
}

void Camera::initInEntity(void)
{
	CameraList.push_back(this->shared_from_this());
	std::sort(CameraList.begin(), CameraList.end(), CameraIdLess);
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

void Camera::_useOrthMatrix(void)
{
	auto owner = getOwner();
	if (!owner || !isEnable()) return;

	auto& trans = owner->transform();
	auto proj = MtxOrtho(mSize.width,mSize.height, mNear, mFar);
	Matrix4x4 lookat;
	Vector3 pos = trans.position;
	pos.x -= mSize.width * 0.5f, pos.y -= mSize.height * 0.5f;
	mLookAt.x = pos.x, mLookAt.y = pos.y;
	bx::mtxLookAt(lookat.matrix, pos.vector, mLookAt.vector, mUp.vector);

	bgfx::setViewTransform(mId, lookat.matrix, proj.matrix);
}

void Camera::_usePresMatrix(void)
{
	auto owner = getOwner();
	if (!owner || !isEnable()) return;

	auto& trans = owner->transform();
	auto proj = MtxProj(mFovy, mSize.width / mSize.height, mNear, mFar,true);
	Matrix4x4 lookat;
	bx::mtxLookAt(lookat.matrix, trans.position.vector, mLookAt.vector, mUp.vector);

	bgfx::setViewTransform(mId, lookat.matrix, proj.matrix);
}

const std::vector<std::shared_ptr<Camera>>& Camera::GetCameras(void)
{
	return CameraList;
}

const std::shared_ptr<Camera> Camera::GetCamera(uint8_t id)
{
	std::shared_ptr<Camera> result(nullptr);
	std::sort(CameraList.begin(), CameraList.end(), CameraIdLess);
	for (auto item : CameraList)
	{
		if (item->mId == id)
		{
			result = item;
			break;
		}
		else if (item->mId > id)
			break;
	}
	return result;
}
