#pragma once
#ifndef __KISSSHOT__ENGINE__BASE__SIZE__
#define __KISSSHOT__ENGINE__BASE__SIZE__

#include "KSBaseMacro.h"

KS_BASE_BEGIN

namespace math { class Vector3; }

class KS_DLL Size final
{
public:
	Size(float w = 0.0f, float h = 0.0f);

	inline Size& scale(float w, float h);
	inline Size& increase(float w, float h);
	inline Size& set(float w, float h);

	inline float length(void) const;

	inline operator math::Vector3(void);
public:
	float width, height;
};

extern inline KS_DLL Size operator+ (const Size& size, const float& num);
extern inline KS_DLL Size operator+ (const float& num, const Size& size);
extern inline KS_DLL Size operator- (const Size& size, const float& num);
extern inline KS_DLL Size operator* (const Size& size, const float& scale);
extern inline KS_DLL Size operator* (const float& scale, const Size& size);
extern inline KS_DLL Size operator/ (const Size& size, const float& scale);
extern inline KS_DLL Size& operator+= (Size& size, const float& num);
extern inline KS_DLL Size& operator-= (Size& size, const float& num);
extern inline KS_DLL Size& operator*= (Size& size, const float& scale);
extern inline KS_DLL Size& operator/= (Size& size, const float& scale);

KS_BASE_END

#endif