#pragma once
#ifndef __KISSSHONT__ENGINE__CORE__COMPONENT__CAMERA__
#define __KISSSHONT__ENGINE__CORE__COMPONENT__CAMERA__

#include "KSIComponent.h"

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
	Camera(const CameraType& type = CameraType::Orthogonal);
	~Camera(void) = default;

	inline Camera& setSize(float w, float h) { mSize.set(w, h); return *this; }
	inline Camera& setSize(const KS_BASE::Size& size) { mSize = size; return *this; }

	inline Camera& setLookAt(float x, float y, float z) { mLookAt.set(x, y, z); return *this; }
	inline Camera& setLookAt(const KS_MATH::Vector3& vec) { mLookAt = vec; return *this; }
	inline Camera& setEyeUp(float x, float y, float z) { mUp.set(x, y, z); return *this; }
	inline Camera& setEyeUp(const KS_MATH::Vector3& vec) { mUp = vec; return *this; }

	KS_MATH::Matrix4x4 getViewMatrix(void);

	inline KS_MATH::Vector3& getLookAt(void) { return mLookAt; }
	inline KS_MATH::Vector3& getEyeUp(void) { return mUp; }

	inline const CameraType& getType(void) const { return mType; }
	inline Camera& setType(const CameraType& type) { mType = type; return *this; }

	inline Camera& setNear(float n) { mNear = n; return *this; }
	inline Camera& setFar(float f) { mFar = f; return *this; }
	inline Camera& setNearAndFar(float n, float f) { mNear = n; mFar = f; return *this; }

	inline const float& getNear(void) const { return mNear; }
	inline const float& getFar(void) const { return mFar; }

	inline Camera& setFovy(float f) { mFovy = f; return *this; }
	inline float getFovy(void) { return mFovy; }

	virtual void use(uint8_t id);

protected:
	virtual KS_MATH::Matrix4x4 _getOrthognalMatrix(void);
	virtual KS_MATH::Matrix4x4 _getPerspectiveMatrix(void);

	virtual void _useOrthMatrix(uint8_t id);
	virtual void _usePresMatrix(uint8_t id);

protected:
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