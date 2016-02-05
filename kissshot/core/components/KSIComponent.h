#pragma once
#ifndef __KISSSHOT__ENGINE__INFTERFACE__COMPONENT__
#define __KISSSHOT__ENGINE__INFTERFACE__COMPONENT__
#include "KSComponentMacro.h"

KS_COMPONENT_BEGIN

class KS_DLL IComponent
{
public:
	IComponent()
		: mTag(0)
	{}
	virtual ~IComponent() {};

	virtual inline const int getTag() const { return mTag; }
	virtual inline void setTag(int tag) { mTag = tag; }

protected:
	int mTag;
};

KS_COMPONENT_END


#endif