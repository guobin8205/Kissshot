#pragma once
#ifndef __KISSSHONT__ENGINE__CORE__COMPONENT__CAMERA__
#define __KISSSHONT__ENGINE__CORE__COMPONENT__CAMERA__

#include "KSIComponent.h"

KS_COMPONENT_BEGIN

class Camera : public IComponent
{
public:
	enum class CameraType
	{
		Orthogonal,
		Perspective
	};

public:
	KSComponentCtor(Camera);
	~Camera(void) = default;

	inline Camera& setLookAt(float x, float y, float z) { mLookAt.set(x, y, z); return *this; }
	inline Camera& setLookAt(const KS_MATH::Vector3& vec) { mLookAt = vec; return *this; }
	inline Camera& setEyeUp(float x, float y, float z) { mUp.set(x, y, z); return *this; }
	inline Camera& setEyeUp(const KS_MATH::Vector3& vec) { mUp = vec; return *this; }

	KS_MATH::Matrix4x4 getViewMatrix(void);

	inline KS_MATH::Vector3& getLookAt(void) { return mLookAt; }
	inline KS_MATH::Vector3& getEyeUp(void) { return mUp; }

	inline const CameraType& getType(void) const { return mType; }
	inline Camera& setType(const CameraType& type) { mType = type; return *this; }

protected:
	KS_MATH::Vector3 mLookAt;
	KS_MATH::Vector3 mUp;

	CameraType mType;
};

KS_REF_TYPE(Camera);

KS_COMPONENT_END

#endif