#include "KSMatrix4x4.h"

KS_MATH_BEGIN

const Matrix4x4 Matrix4x4::Zero({
	0.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 0.0f, 0.0f
});
const Matrix4x4 Matrix4x4::Identity;

KS_MATH_END