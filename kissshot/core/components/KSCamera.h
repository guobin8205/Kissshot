#pragma once
#ifndef __KISSSHONT__ENGINE__CORE__COMPONENT__CAMERA__
#define __KISSSHONT__ENGINE__CORE__COMPONENT__CAMERA__

#include "KSIComponent.h"
#include <vector>
#include <memory>
KS_COMPONENT_BEGIN

typedef uint8_t CameraMask;

class Camera : public IComponent,public std::enable_shared_from_this<Camera>
{
public:
	enum class CameraType
	{
		Orthogonal,
		Perspective
	};


public:
	Camera(const CameraType& type = CameraType::Orthogonal,float _near = 0.1f,float _far = 100.0f,float _fovy = 60.0f);
	~Camera(void);

	virtual void setClearCamera(uint16_t flags, uint32_t rgba = 0x000000FFU, float depth = 1.0f, uint8_t stencil = 0);
	KS_MATH::Matrix4x4 getViewMatrix(void);

	virtual void use(void);

	static const std::vector<std::shared_ptr<Camera>>& GetCameras(void);
	static const std::shared_ptr<Camera> GetCamera(uint8_t id);

protected:
	virtual KS_MATH::Matrix4x4 _getOrthognalMatrix(void);
	virtual KS_MATH::Matrix4x4 _getPerspectiveMatrix(void);

	virtual void _useOrthMatrix(void);
	virtual void _usePresMatrix(void);

	void destoryInEntity(void) override;
	void initInEntity(void) override;

public:
	KS_MATH::Vector3 mLookAt;
	KS_MATH::Vector3 mUp;
	KS_BASE::Size mSize;

	float mNear, mFar, mFovy;

	CameraType mType;
	uint8_t mId;

};

KS_REF_TYPE(Camera);

KS_COMPONENT_END

#endif