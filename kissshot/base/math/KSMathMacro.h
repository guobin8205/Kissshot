#pragma once

#ifndef __KISSSHOT__ENGINE__MATHMACRO__
#define __KISSSHOT__ENGINE__MATHMACRO__
#include "../KSBaseMacro.h"

#define KS_MATH_BEGIN KS_BASE_BEGIN namespace math {
#define KS_MATH_END } KS_BASE_END
#define KS_MATH KS_BASE::math
#define KS_USE_MATH using namespace KS_MATH

#define KS_MATH_COMPARE_DEV (1.0f)

#endif