#pragma once
#ifndef __KISSSHOT__ENGINE__ENTITY__
#define __KISSSHOT__ENGINE__ENTITY__

#include "../../KSMacro.h"
#include <vector>
#include <unordered_map>
#include <atomic>
#include <memory>
#include "../../base/KSTransform.h"
#include "../components/KSIComponent.h"

KS_BEGIN

class Transform;

class KS_DLL Entity final
{
public:
	typedef std::unordered_multimap<size_t, std::shared_ptr<component::IComponent>> ComponentMap;
	Entity(void) {};
	~Entity(void) {};
	
	template<typename T>
	std::shared_ptr<T> addComponent(void)
	{
		static_assert(::std::is_base_of<component::IComponent, T>::value, "T must base of compnent::IComponent");

		std::shared_ptr<T> ptr(new T());
		mComponents.insert(ComponentMap::value_type(typeid(T).hash_code(), std::static_pointer_cast<component::IComponent,T>(ptr)));
		return ptr;
	}

	template<typename T>
	std::shared_ptr<T> getComponent(void)
	{
		static_assert(::std::is_base_of<component::IComponent, T>::value, "T must base of compnent::IComponent");

		auto ptr = mComponents.find(typeid(T).hash_code());
		if (ptr == mComponents.end()) return std::shared_ptr<T>(nullptr);
		return std::static_pointer_cast<T, ComponentMap::mapped_type::element_type>(ptr->second);
	}

	template<typename T>
	size_t getComponents(ComponentMap::iterator& out)
	{
		static_assert(::std::is_base_of<component::IComponent, T>::value, "T must base of compnent::IComponent");

		size_t length = 0;
		length = mComponents.count(typeid(T).hash_code());
		if (length)
			out = mComponents.find(typeid(T).hash_code());
	}

	template<typename T>
	void removeComponents(void)
	{
		static_assert(::std::is_base_of<component::IComponent, T>::value, "T must base of compnent::IComponent");

		mComponents.erase(typeid(T).hash_code());
	}

	template<typename T>
	void removeComponent(int tag)
	{
		static_assert(::std::is_base_of<component::IComponent, T>::value, "T must base of compnent::IComponent");

		auto find = mComponents.find(typeid(T).hash_code());
		while (find != mComponents.end())
		{
			if (find->second->getTag() == tag)
			{
				mComponents.erase(find);
				break;
			}
			++find;
		}
	}

private:
	Transform mTransform;
	ComponentMap mComponents;
	
};

KS_END


#endif