#include "KSSize.h"
#include "math/KSVector3.h"
#include <bx/fpumath.h>
KS_BASE_BEGIN

Size::Size(float w, float h)
	: width(w)
	, height(h)
{
}

Size& Size::scale(float w, float h)
{
	width *= w, height *= h;
	return *this;
}

Size& Size::increase(float w, float h)
{
	width += w, height += h;
	return *this;
}

Size& Size::set(float w, float h)
{
	width = w, height = h;
	return *this;
}

float Size::length(void) const
{
	float ww = width * width, hh = height * height;
	return bx::fsqrt(ww + hh);
}

Size::operator math::Vector3(void)
{
	return  math::Vector3(width, height, 1.0f);
}

inline Size operator+(const Size & size, const float & num)
{
	Size result(size.width, size.height);
	result.increase(num, num);
	return result;
}

inline Size operator+(const float & num, const Size & size)
{
	Size result(size.width, size.height);
	result.increase(num, num);
	return result;
}

inline Size operator-(const Size & size, const float & num)
{
	Size result(size.width, size.height);
	result.increase(-num, -num);
	return result;
}

inline Size operator*(const Size & size, const float & scale)
{
	Size result(size.width, size.height);
	result.scale(scale, scale);
	return result;
}

inline Size operator*(const float & scale, const Size & size)
{
	Size result(size.width, size.height);
	result.scale(scale, scale);
	return result;
}

inline Size operator/(const Size & size, const float & scale)
{
	Size result(size.width, size.height);
	auto s = 1 / scale;
	result.scale(s, s);
	return result;
}

inline Size & operator+=(Size& size, const float & num)
{
	size.increase(num, num);
	return size;
}

inline Size & operator-=(Size& size, const float & num)
{
	size.increase(-num, -num);
	return size;
}

inline Size & operator*=(Size & size, const float & scale)
{
	size.scale(scale, scale);
	return size;
}

inline Size & operator/=(Size & size, const float & scale)
{
	auto s = 1 / scale;
	size.scale(s, s);
	return size;
}





KS_BASE_END


