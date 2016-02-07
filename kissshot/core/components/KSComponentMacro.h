#pragma once

#ifndef __KISSSHOT__ENGINE__COMPONENT__MACRO__
#define __KISSSHOT__ENGINE__COMPONENT__MACRO__

#include "../KSCoreMacro.h"

#define KS_COMPONENT_BEGIN KS_CORE_BEGIN namespace component{
#define KS_COMPONENT_END } KS_CORE_END

#define KS_COMPONENT KS_CORE::component
#define KS_USE_COMPONENT using namespace KS_COMPONENT

#define KSComponentCtor(CLASS,...) \
CLASS(void) = delete; \
CLASS(const CLASS&) = delete; \
CLASS(::kissshot::core::container::Entity& owner,__VA_ARGS__)

#define KSComponentCtorDef(CLASS,...) \
CLASS::CLASS(::kissshot::core::container::Entity& owner,__VA_ARGS__)

#endif