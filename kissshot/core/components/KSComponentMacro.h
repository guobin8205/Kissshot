#pragma once

#ifndef __KISSSHOT__ENGINE__COMPONENT__MACRO__
#define __KISSSHOT__ENGINE__COMPONENT__MACRO__

#include "../KSCoreMacro.h"

#define KS_COMPONENT_BEGIN KS_CORE_BEGIN namespace component{
#define KS_COMPONENT_END } KS_CORE_END

#define KS_COMPONENT KS_CORE::component
#define KS_USE_COMPONENT using namespace KS_COMPONENT

#define KSComponentCtor(CLASS) \
CLASS operator= (const CLASS& other) = delete; \
CLASS(const CLASS&) = delete; \
CLASS()

#define KSPtr2ICom(SHARE,TYPE) std::static_pointer_cast<KS_CORE::component::IComponent, TYPE>(SHARE)
#define KSICom2Type(SHARE,TYPE) std::static_pointer_cast<TYPE,KS_CORE::component::IComponent>(SHARE)

#define KSComponentCtorDef(CLASS) \
CLASS::CLASS()

#endif