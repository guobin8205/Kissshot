#pragma once
#ifndef __KISSSHONT__ENGINE__CORE__COMPONENT__CAMERA__
#define __KISSSHONT__ENGINE__CORE__COMPONENT__CAMERA__

#include "KSIComponent.h"

KS_COMPONENT_BEGIN

class Camera : public IComponent
{
public:
	KSComponentCtor(Camera)
		: IComponent(owner)
		, mLookAt(0.0f, 0.0f, 0.0f)
		, mUp(0.0f, 1.0f, 0.0f)
	{
	}
	~Camera(void) {};

	inline Camera& setLookAt(float x, float y, float z) { mLookAt.set(x, y, z); return *this; }
	inline Camera& setLookAt(const KS_MATH::Vector3& vec) { mLookAt = vec; return *this; }
	inline Camera& setEyeUp(float x, float y, float z) { mUp.set(x, y, z); return *this; }
	inline Camera& setEyeUp(const KS_MATH::Vector3& vec) { mUp = vec; return *this; }

	KS_MATH::Matrix4x4 getViewMatrix(void);

	inline KS_MATH::Vector3& getLookAt(void) { return mLookAt; }
	inline KS_MATH::Vector3& getEyeUp(void) { return mUp; }
protected:
	KS_MATH::Vector3 mLookAt;
	KS_MATH::Vector3 mUp;
};

KS_COMPONENT_END

#endif