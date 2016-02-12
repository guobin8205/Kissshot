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
		, mUid(0)
		, mOwner(nullptr)
		, mIsEnable(true)
	{}

	virtual ~IComponent();

	virtual inline const uint32& getTag() const { return mTag; }
	virtual inline void setTag(uint32 tag) { mTag = tag; }

	KS_CORE::container::Entity* const getOwner() { return mOwner; }
	virtual void setOwner(std::shared_ptr<KS_CORE::container::Entity> other);

	virtual inline void setEnable(bool enable) { mIsEnable = enable; }
	virtual inline const bool& isEnable(void) const { return mIsEnable; }

	virtual inline const uint32& getUid(void) const { return mUid; }


	friend class KS_CORE::container::Entity;

protected:
	virtual void destoryInEntity(void);
	virtual void initInEntity(void) = 0;

protected:
	uint32 mTag;
	KS_CORE::container::Entity* mOwner;
	bool mIsEnable;

private:
	uint32 mUid;
};

KS_REF_TYPE(IComponent);

KS_COMPONENT_END


#endif