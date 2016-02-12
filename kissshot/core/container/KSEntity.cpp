#include "KSEntity.h"
#include "components/KSIComponent.h"
#include "KSDebug.h"
#include "KSStringUtil.h"
KS_CORE_CONTAINER_BEGIN

#define ENTITY_COMPONENT_INIT_SIZE	4
#define KS_UINT_MAX 0xFFFFFFF0U


Entity::Entity(void)
	: mUidCount(0)
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
	_checkUid();
	auto owner = ptr->getOwner();
	if (owner == this)
	{
		KSLOG(L"KS Warning:owner of ptr is same of this in Entity::addComponent");
	}
	else
	{
		uint32 hash = CLASS_PTR_HASH(ptr.get());
		ptr->setOwner(nullptr);
		mComponents.insert(ComponentMap::value_type(hash, ptr));
		ptr->mOwner = this;
		ptr->mUid = ++mUidCount;
		ptr->initInEntity();
	}
	return ptr;
}

void Entity::removeComponents(uint32 hashcode)
{
	auto list = mComponents.equal_range(hashcode);
	for (auto itor = list.first; itor != list.second; ++itor)
	{
		itor->second->setOwner(nullptr);
		itor->second->destoryInEntity();
	}

	mComponents.erase(hashcode);
}

std::shared_ptr<KS_CORE::component::IComponent> Entity::removeComponent(uint32 hashcode, uint32 uid)
{
	auto list = mComponents.equal_range(hashcode);
	std::shared_ptr<KS_CORE::component::IComponent> result(nullptr);

	for (auto itor = list.first; itor != list.second; ++itor)
	{
		if (itor->second->getUid() == uid)
		{
			result = itor->second;
			mComponents.erase(itor);
			result->setOwner(nullptr);
			result->destoryInEntity();
			break;
		}
	}
	return result;
}

std::shared_ptr<KS_CORE::component::IComponent> Entity::removeComponent(std::shared_ptr<KS_CORE::component::IComponent> com)
{
	auto hash_code = CLASS_PTR_HASH(com.get());
	auto uid = com->getUid();
	removeComponent(hash_code, uid);
	return com;
}

void Entity::_refreshUid(void)
{
	uint32 uid = 0;
	for (auto& itor : mComponents)
	{
		++uid;
		itor.second->mUid = uid;
	}
	mUidCount = uid;

}

void Entity::_checkUid(void)
{
	if (mUidCount == KS_UINT_MAX)
		_refreshUid();

	KSBREAK(mUidCount > KS_UINT_MAX);
}

KS_CORE_CONTAINER_END

