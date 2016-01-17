#pragma once

#ifndef __KISSSHOT__ENGINE__TRANSFORM__
#define __KISSSHOT__ENGINE__TRANSFORM__

#include "KSMacro.h"
#include "KSMath.h"
KS_BEGIN

class KS_DLL Transform
{
public:
	math::Matrix4x4 getMatrix();



public:
	math::Vector3 position;
	math::Vector3 scale;
	math::Vector3 rotate;
};

KS_END

#endif