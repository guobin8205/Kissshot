#pragma once

#ifndef __KISSSHOT__ENGINE__APPDELEGATE__
#define __KISSSHOT__ENGINE__APPDELEGATE__

#include "../KSMacro.h"

KS_BEGIN

class AppDelegate
{
public:
	AppDelegate();

	virtual void init() = 0;
	virtual int run();
	virtual void stop();
	virtual void resume();
	virtual void shutdown();
};

KS_END

#endif