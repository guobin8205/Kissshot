#pragma once

#ifndef __KISSSHOT__ENGINE__TRANSFORM__
#define __KISSSHOT__ENGINE__TRANSFORM__

#include "KSMacro.h"
#include "KSMath.h"
KS_BEGIN
class Vector3;
class Matrix4x4;

class KS_DLL Transform
{
public:
	Matrix4x4 getMatrix();



public:
	Vector3 position;
	Vector3 scale;
	Vector3 rotate;
};

KS_END

#endif