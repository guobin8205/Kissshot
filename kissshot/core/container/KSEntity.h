#pragma once
#ifndef __KISSSHOT__ENGINE__ENTITY__
#define __KISSSHOT__ENGINE__ENTITY__

#include <vector>
#include <unordered_map>
#include <atomic>
#include <vector>
#include <memory>
#include "KSContainerMacro.h"

KS_CORE_BEGIN namespace component { class IComponent; } KS_CORE_END;
KS_CORE_CONTAINER_BEGIN

class KS_DLL Entity final
{
public:
	typedef std::unordered_multimap<size_t, std::shared_ptr<KS_CORE::component::IComponent>> ComponentMap;

	Entity(void);
	~Entity(void);
	
	template<typename T,typename ...Tx>
	std::shared_ptr<T> addComponent(Tx... parmes);

	std::shared_ptr<KS_CORE::component::IComponent> addComponent(std::shared_ptr<KS_CORE::component::IComponent> ptr);

	template<typename T>
	std::shared_ptr<T> getComponent(void);

	template<typename T>
	std::shared_ptr<std::vector<std::shared_ptr<T>>> getComponents();

	template<typename T>
	void removeComponents(void);

	template<typename T>
	std::shared_ptr<T> removeComponent(int tag);

	void removeComponents(uint32 hashcode);
	std::shared_ptr<KS_CORE::component::IComponent> removeComponent(uint32 hashcode, uint32 uid);

	std::shared_ptr<KS_CORE::component::IComponent> removeComponent(std::shared_ptr<KS_CORE::component::IComponent> com);

	inline KS_BASE::Transform& transform() { return mTransform; }
	inline KS_MATH::Matrix4x4 getMatrix() { return mTransform.getMatrix(); }

private:
	void _refreshUid(void);
	void _checkUid(void);

private:
	KS_BASE::Transform mTransform;
	ComponentMap mComponents;
	uint32 mUidCount;
};

template<typename T, typename ...Tx>
std::shared_ptr<T> Entity::addComponent(Tx... parmes)
{
	static_assert(::std::is_base_of<KS_CORE::component::IComponent, T>::value, "T must base of compnent::IComponent");
	_checkUid();

	std::shared_ptr<T> ptr(new T(parmes...));
	auto iptr = std::static_pointer_cast<KS_CORE::component::IComponent, T>(ptr);
	mComponents.insert(ComponentMap::value_type(CLASS_HASH(T), iptr));
	iptr->mOwner = this;
	iptr->mUid = ++mUidCount;
	iptr->initInEntity();
	return ptr;
}

template<typename T>
std::shared_ptr<T> Entity::getComponent(void)
{
	static_assert(::std::is_base_of<KS_CORE::component::IComponent, T>::value, "T must base of compnent::IComponent");

	auto ptr = mComponents.find(CLASS_HASH(T));
	if (ptr == mComponents.end()) return std::shared_ptr<T>(nullptr);
	return std::static_pointer_cast<T, ComponentMap::mapped_type::element_type>(ptr->second);
}


template<typename T>
std::shared_ptr<std::vector<std::shared_ptr<T>>> Entity::getComponents()
{
	static_assert(::std::is_base_of<KS_CORE::component::IComponent, T>::value, "T must base of compnent::IComponent");

	size_t count = 0;
	count = mComponents.count(CLASS_HASH(T));

	std::vector<std::shared_ptr<T>>* result = new std::vector<std::shared_ptr<T>>();
	result->reserve(count);

	auto list = mComponents.equal_range(CLASS_HASH(T));
	
	for (auto itor = list.first; itor != list.second; ++itor)
		result->push_back(std::static_pointer_cast<T, ComponentMap::mapped_type::element_type>(itor->second));

	return std::shared_ptr<std::vector<std::shared_ptr<T>>>(result);
}

template<typename T>
void Entity::removeComponents(void)
{
	static_assert(::std::is_base_of<KS_CORE::component::IComponent, T>::value, "T must base of compnent::IComponent");
	removeComponents(CLASS_HASH(T));
}

template<typename T>
std::shared_ptr<T> Entity::removeComponent(int tag)
{
	static_assert(::std::is_base_of<KS_CORE::component::IComponent, T>::value, "T must base of compnent::IComponent");

	std::shared_ptr<T> result;
	auto find = mComponents.equal_range(CLASS_HASH(T));
	for (auto itor = find.first; itor != find.second; ++itor)
	{
		if (itor->second->getTag() == tag)
		{
			itor->destory();
			mComponents.erase(find);
			result = std::static_pointer_cast<T, ComponentMap::mapped_type::element_type>(itor->second);
			break;
		}
	}
	return result;
}

KS_REF_TYPE(Entity);

KS_CORE_CONTAINER_END

#endif