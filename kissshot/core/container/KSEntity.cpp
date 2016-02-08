#include "KSEntity.h"
#include "components/KSIComponent.h"
#include "KSDebug.h"
#include "KSStringUtil.h"
KS_CORE_CONTAINER_BEGIN

#define ENTITY_COMPONENT_INIT_SIZE	4

Entity::Entity(void)
{
	mComponents.reserve(ENTITY_COMPONENT_INIT_SIZE);
}

Entity::~Entity(void)
{
	for (auto& item : mComponents)
		item.second->mOwner = nullptr;
	mComponents.clear();
}

std::shared_ptr<KS_CORE::component::IComponent> Entity::addComponent(std::shared_ptr<KS_CORE::component::IComponent> ptr)
{
	auto owner = ptr->getOwner();
	if (owner == this)
	{
		KSLOG(L"KS Warning:owner of ptr is same of this in Entity::addComponent");
	}
	else
	{
		uint32 hash = typeid(*ptr.get()).hash_code();
		mComponents.insert(ComponentMap::value_type(hash, ptr));
		ptr->setOwner(this);
	}
	return ptr;
}

std::shared_ptr<KS_CORE::component::IComponent> Entity::removeComponent(KS_CORE::component::IComponent* com)
{
	uint32 hash = typeid(com).hash_code();
	auto list = mComponents.equal_range(hash);
	std::shared_ptr<KS_CORE::component::IComponent> result(nullptr);

	for (auto itor = list.first; itor != list.second; ++itor)
	{
		if (itor->second.get() == com)
		{
			result = itor->second;
			mComponents.erase(itor);
			result->setOwner(nullptr);
			break;
		}
	}
	return result;
}

KS_CORE_CONTAINER_END

