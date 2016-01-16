#pragma once
#ifndef __KISSSHOT__ENGINE__ENTITY__
#define __KISSSHOT__ENGINE__ENTITY__

#include "KSMacro.h"
#include <vector>
KS_BEGIN

class KS_DLL Entity final
{
public:
	Entity(void);
	~Entity(void);
	
	template<typename T>
	T* addComponent(void);

	template<typename T>
	T* getComponent(void);

	template<typename T>
	std::vector<T*>* getComponents(void);

private:

};

KS_END


#endif