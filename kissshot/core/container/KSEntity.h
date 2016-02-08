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
	
	template<typename T>
	std::shared_ptr<T> addComponent(void);

	std::shared_ptr<KS_CORE::component::IComponent> addComponent(std::shared_ptr<KS_CORE::component::IComponent> ptr);

	template<typename T>
	std::shared_ptr<T> getComponent(void);

	template<typename T>
	std::shared_ptr<std::vector<std::shared_ptr<T>>> getComponents();

	template<typename T>
	void removeComponents(void);

	template<typename T>
	void removeComponent(int tag);

	std::shared_ptr<KS_CORE::component::IComponent> removeComponent(KS_CORE::component::IComponent* com);

	inline KS_BASE::Transform& transform() { return mTransform; }
	inline KS_MATH::Matrix4x4 getMatrix() { return mTransform.getMatrix(); }
private:
	KS_BASE::Transform mTransform;
	ComponentMap mComponents;
	
};

template<typename T>
std::shared_ptr<T> Entity::addComponent(void)
{
	static_assert(::std::is_base_of<KS_CORE::component::IComponent, T>::value, "T must base of compnent::IComponent");

	std::shared_ptr<T> ptr(new T());
	mComponents.insert(ComponentMap::value_type(typeid(T).hash_code(), std::static_pointer_cast<KS_CORE::component::IComponent, T>(ptr)));
	ptr->mOwner = this;
	return ptr;
}

template<typename T>
std::shared_ptr<T> Entity::getComponent(void)
{
	static_assert(::std::is_base_of<KS_CORE::component::IComponent, T>::value, "T must base of compnent::IComponent");

	auto ptr = mComponents.find(typeid(T).hash_code());
	if (ptr == mComponents.end()) return std::shared_ptr<T>(nullptr);
	return std::static_pointer_cast<T, ComponentMap::mapped_type::element_type>(ptr->second);
}


template<typename T>
std::shared_ptr<std::vector<std::shared_ptr<T>>> Entity::getComponents()
{
	static_assert(::std::is_base_of<KS_CORE::component::IComponent, T>::value, "T must base of compnent::IComponent");

	size_t count = 0;
	count = mComponents.count(typeid(T).hash_code());

	std::vector<std::shared_ptr<T>>* result = new std::vector<std::shared_ptr<T>>();
	result->reserve(count);

	auto list = mComponents.equal_range(typeid(T).hash_code());
	
	for (auto itor = list.first; itor != list.second; ++itor)
		result->push_back(std::static_pointer_cast<T, ComponentMap::mapped_type::element_type>(itor->second));

	return std::shared_ptr<std::vector<std::shared_ptr<T>>>(result);
}

template<typename T>
void Entity::removeComponents(void)
{
	static_assert(::std::is_base_of<KS_CORE::component::IComponent, T>::value, "T must base of compnent::IComponent");

	mComponents.erase(typeid(T).hash_code());
}

template<typename T>
void Entity::removeComponent(int tag)
{
	static_assert(::std::is_base_of<KS_CORE::component::IComponent, T>::value, "T must base of compnent::IComponent");

	auto find = mComponents.equal_range(typeid(T).hash_code());
	for (auto itor = find.first; itor != find.second; ++itor)
	{
		if (find->second->getTag() == tag)
		{
			mComponents.erase(find);
			break;
		}
	}
}

KS_CORE_CONTAINER_END

#endif