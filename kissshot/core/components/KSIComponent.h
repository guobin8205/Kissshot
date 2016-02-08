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
	IComponent(void)
		: mTag(0)
		, mOwner(nullptr)
	{}

	virtual ~IComponent();

	virtual inline const int getTag() const { return mTag; }
	virtual inline void setTag(int tag) { mTag = tag; }

	KS_CORE::container::Entity* const getOwner() { return mOwner; }
	virtual void setOwner(KS_CORE::container::Entity* other);

	virtual inline void setEnable(bool enable) { mIsEnable = enable; }
	virtual inline const bool& isEnable(void) const { return mIsEnable; }

	friend class KS_CORE::container::Entity;
protected:
	int mTag;
	KS_CORE::container::Entity* mOwner;
	bool mIsEnable;
};

KS_COMPONENT_END


#endif