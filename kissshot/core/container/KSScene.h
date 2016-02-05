#pragma once


#ifndef __KISSSHOT__ENGINE__SCENE__
#define __KISSSHOT__ENGINE__SCENE__
#include "KSMacro.h"
#include <memory>
#include <stack>

KS_CORE_CONTAINER_BEGIN

class KS_DLL Scene
{
public:
	Scene(void);
	~Scene(void);



private:
	static std::stack<std::shared_ptr<Scene>> mScenes;
};

KS_CORE_CONTAINER_END

#endif