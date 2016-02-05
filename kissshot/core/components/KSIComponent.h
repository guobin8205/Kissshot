#pragma once
#ifndef __KISSSHOT__ENGINE__INFTERFACE__COMPONENT__
#define __KISSSHOT__ENGINE__INFTERFACE__COMPONENT__
#include "KSComponentMacro.h"
#include <memory>

namespace kissshot { namespace core { namespace container { class Entity; } } };

KS_COMPONENT_BEGIN

class KS_DLL IComponent
{
public:
	KSComponentCtor(IComponent)
		: mTag(0)
		, mOwner(owner)
	{}

	virtual ~IComponent() {};

	virtual inline const int getTag() const { return mTag; }
	virtual inline void setTag(int tag) { mTag = tag; }
	kissshot::core::container::Entity& getOwner() { return mOwner; }

protected:
	int mTag;
	kissshot::core::container::Entity& mOwner;
};

KS_COMPONENT_END


#endif