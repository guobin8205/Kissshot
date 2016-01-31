
#include "kissshot.h"

using namespace bgfx;

class AppDelegate final
{
public:
	AppDelegate() {};

	int init(int argc, char **argv)
	{
		::init();
		::reset(1280, 720, BGFX_RESET_VSYNC);
		::setDebug(BGFX_DEBUG_TEXT);
		::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0XFF000000);
		return true;
	};

	int update()
	{
		::setViewRect(0, 0, 0, 1280, 720);
		::touch(0);
		::dbgTextClear();
		::dbgTextPrintf(0, 0, 0x4f, "aaaaaa");
		::frame();
		return 1;
	}
};

int _main_(int argc, char **argv)
{
	AppDelegate app;
	app.init(argc, argv);
	while (app.update());
	return 0;
}