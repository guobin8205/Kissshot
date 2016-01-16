#pragma once

#ifndef __KISSSHOT__ENGINE__TRANSFORM__
#define __KISSSHOT__ENGINE__TRANSFORM__

#include "KSMacro.h"

KS_BEGIN

class KS_DLL Transform
{
public:
protected:
	float _position[4];
	float _roation[4];
	float _scale[3];
};

KS_END

#endif