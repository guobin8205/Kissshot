#pragma once

#ifndef __KISSSHOT__ENGINE__ENTERNAL__ENTRY__
#define __KISSSHOT__ENGINE__ENTERNAL__ENTRY__
#include <bgfx/bgfx.h>
#include <bx/uint32_t.h>
#include "../../kissshot.h"
#include <bx/fpumath.h>
KS_USE_CORE_CONTAINER;
KS_USE_COMPONENT;

extern const uint8_t s_logo[4000];

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
	};

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorVertex::ms_decl;

static PosColorVertex s_cubeVertices[8] =
{
	{ -1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{ -1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{ -1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{ -1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t s_cubeIndices[36] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

typedef Camera& (Camera::*Fun)(float);

int _main_(int argc, char **argv)
{
	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init();
	bgfx::reset(width, height, reset);

	// Enable debug text.
	bgfx::setDebug(debug);

	{
		Camera camera;
		int a = 10;
	}

	EntityRef e(new Entity());
	CameraRef camera(new Camera());
	auto& cameras = Camera::GetCameras();
	camera->setClearCamera(BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xFF0000FF);
	e->addComponent(camera);
	camera->mLookAt.set(0.0f, 0.0f, 0.0f);

	// Create vertex stream declaration.
	PosColorVertex::init();

	// Create static vertex buffer.
	auto m_vbh = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices))
		, PosColorVertex::ms_decl
		);

	// Create static index buffer.
	auto m_ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices))
		);

	auto fs = kissshot::utils::Storage::getInstance()->getDataFromFile(L"Assets/fs_cubes.bin");
	auto fsm = bgfx::copy(fs.getData().get(), fs.getSize());
	auto fhandle = bgfx::createShader(fsm);

	auto vs = kissshot::utils::Storage::getInstance()->getDataFromFile(L"Assets/vs_cubes.bin");
	auto vsm = bgfx::copy(vs.getData().get(), vs.getSize());
	auto vhandle = bgfx::createShader(vsm);

	auto program = bgfx::createProgram(vhandle, fhandle);

	auto pos = kissshot::base::Transform();
	pos.position.set(0.0f, 0.0f, 0.0f);

	e->transform().position.set(0.0f, 0.0f, - 10.0f);


	while (true)
	{
		static int i = 0;
		static int add = 1;

		camera->use();

		bgfx::setViewRect(0, 0, 0, width, height);

		bgfx::touch(0);

		bgfx::setTransform(pos.getMatrix().matrix);

		bgfx::setVertexBuffer(m_vbh);
		bgfx::setIndexBuffer(m_ibh);

		bgfx::setState(BGFX_STATE_DEFAULT);

		bgfx::submit(0, program);

		bgfx::frame();

		bgfx::saveScreenShot(KS_W2A(kissshot::utils::Storage::getInstance()->getWritablePath() + L"/aa").c_str());
		//break;
	}

	//bgfx::saveScreenShot(KS_W2A(kissshot::utils::Storage::getInstance()->getWritablePath() + L"/aa").c_str());
	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}


const uint8_t s_logo[4000] =
{
	0xdc, 0x03, 0xdc, 0x03, 0xdc, 0x03, 0xdc, 0x03, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, // ........ . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0xdc, 0x08, //  . . . . . . ...
	0xdc, 0x03, 0xdc, 0x07, 0xdc, 0x07, 0xdc, 0x08, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, // ........ . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0xde, 0x03, 0xb0, 0x3b, 0xb1, 0x3b, 0xb2, 0x3b, 0xdb, 0x3b, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, // ...;.;.;.; . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0xdc, 0x03, 0xb1, 0x3b, 0xb2, 0x3b, //  . . . . ....;.;
	0xdb, 0x3b, 0xdf, 0x03, 0xdf, 0x3b, 0xb2, 0x3f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, // .;...;.? . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0xb1, 0x3b, 0xb1, 0x3b, 0xb2, 0x3b, 0xb2, 0x3f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  ..;.;.;.? . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0xb1, 0x3b, 0xb1, 0x3b, 0xb2, 0x3b, //  . . . . ..;.;.;
	0xb2, 0x3f, 0x20, 0x0f, 0x20, 0x0f, 0xdf, 0x03, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, // .? . ... . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0xb1, 0x3b, 0xb1, 0x3b, 0xb1, 0x3b, 0xb1, 0x3f, 0xdc, 0x0b, 0xdc, 0x03, 0xdc, 0x03, //  ..;.;.;.?......
	0xdc, 0x03, 0xdc, 0x03, 0x20, 0x0f, 0x20, 0x0f, 0xdc, 0x08, 0xdc, 0x03, 0xdc, 0x03, 0xdc, 0x03, // .... . .........
	0xdc, 0x03, 0xdc, 0x03, 0xdc, 0x03, 0xdc, 0x08, 0x20, 0x0f, 0xb1, 0x3b, 0xb1, 0x3b, 0xb1, 0x3b, // ........ ..;.;.;
	0xb1, 0x3f, 0xb1, 0x3f, 0xb2, 0x0b, 0x20, 0x0f, 0x20, 0x0f, 0xdc, 0x03, 0xdc, 0x03, 0xdc, 0x03, // .?.?.. . .......
	0x20, 0x0f, 0x20, 0x0f, 0xdc, 0x03, 0xdc, 0x03, 0xdc, 0x03, 0x20, 0x0f, 0x20, 0x01, 0x20, 0x0f, //  . ....... . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0xb2, 0x3b, 0xb1, 0x3b, 0xb0, 0x3b, 0xb0, 0x3f, 0x20, 0x0f, 0xde, 0x03, 0xb0, 0x3f, //  ..;.;.;.? ....?
	0xb1, 0x3f, 0xb2, 0x3f, 0xdd, 0x03, 0xde, 0x03, 0xdb, 0x03, 0xdb, 0x03, 0xb2, 0x3f, 0x20, 0x0f, // .?.?.........? .
	0x20, 0x0f, 0xb0, 0x3f, 0xb1, 0x3f, 0xb2, 0x3f, 0xde, 0x38, 0xb2, 0x3b, 0xb1, 0x3b, 0xb0, 0x3b, //  ..?.?.?.8.;.;.;
	0xb0, 0x3f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0xb0, 0x3b, 0xb1, 0x3b, 0xb2, 0x3b, 0xb2, 0x3f, // .? . . ..;.;.;.?
	0xdd, 0x03, 0xde, 0x03, 0xb0, 0x3f, 0xb1, 0x3f, 0xb2, 0x3f, 0xdd, 0x03, 0x20, 0x01, 0x20, 0x0f, // .....?.?.?.. . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0xb2, 0x3b, 0xb1, 0x3b, 0xb0, 0x3b, 0xb0, 0x3f, 0x20, 0x0f, 0x20, 0x0f, 0xdb, 0x03, //  ..;.;.;.? . ...
	0xb0, 0x3f, 0xb1, 0x3f, 0xdd, 0x03, 0xb1, 0x3b, 0xb0, 0x3b, 0xdb, 0x03, 0xb1, 0x3f, 0x20, 0x0f, // .?.?...;.;...? .
	0x20, 0x0f, 0x20, 0x3f, 0xb0, 0x3f, 0xb1, 0x3f, 0xb0, 0x3b, 0xb2, 0x3b, 0xb1, 0x3b, 0xb0, 0x3b, //  . ?.?.?.;.;.;.;
	0xb0, 0x3f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0xdc, 0x08, 0xdc, 0x3b, 0xb1, 0x3b, 0xb1, 0x3f, // .? . . ....;.;.?
	0xb1, 0x3b, 0xb0, 0x3b, 0xb2, 0x3b, 0xb0, 0x3f, 0xdc, 0x03, 0x20, 0x0f, 0x20, 0x01, 0x20, 0x0f, // .;.;.;.?.. . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0xb2, 0x3b, 0xb1, 0x3b, 0xb0, 0x3b, 0xb0, 0x3f, 0xdc, 0x0b, 0xdc, 0x07, 0xdb, 0x03, //  ..;.;.;.?......
	0xdb, 0x03, 0xdc, 0x38, 0x20, 0x0f, 0xdf, 0x03, 0xb1, 0x3b, 0xb0, 0x3b, 0xb0, 0x3f, 0xdc, 0x03, // ...8 ....;.;.?..
	0xdc, 0x07, 0xb0, 0x3f, 0xb1, 0x3f, 0xb2, 0x3f, 0xdd, 0x3b, 0xb2, 0x3b, 0xb1, 0x3b, 0xdc, 0x78, // ...?.?.?.;.;.;.x
	0xdf, 0x08, 0x20, 0x0f, 0x20, 0x0f, 0xde, 0x08, 0xb2, 0x3b, 0xb1, 0x3b, 0xb0, 0x3b, 0xb0, 0x3f, // .. . ....;.;.;.?
	0x20, 0x0f, 0xdf, 0x03, 0xb1, 0x3b, 0xb2, 0x3b, 0xdb, 0x03, 0xdd, 0x03, 0x20, 0x01, 0x20, 0x0f, //  ....;.;.... . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0xdc, 0x08, 0xdc, 0x08, 0xdc, 0x08, 0x20, 0x0f, //  . . . ....... .
	0x20, 0x0f, 0xb0, 0x3f, 0xb0, 0x3f, 0xb1, 0x3f, 0xdd, 0x3b, 0xdb, 0x0b, 0xdf, 0x03, 0x20, 0x0f, //  ..?.?.?.;.... .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0xdf, 0x08, 0xdf, 0x03, 0xdf, 0x03, 0xdf, 0x08, //  . . . .........
	0x20, 0x0f, 0x20, 0x0f, 0xdf, 0x08, 0xdf, 0x03, 0xdf, 0x03, 0x20, 0x0f, 0x20, 0x01, 0x20, 0x0f, //  . ....... . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0xdb, 0x08, 0xb2, 0x38, 0xb1, 0x38, 0xdc, 0x03, //  . . . ....8.8..
	0xdc, 0x07, 0xb0, 0x3b, 0xb1, 0x3b, 0xdf, 0x3b, 0xdf, 0x08, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, // ...;.;.;.. . . .
	0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
	0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
	0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
	0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
	0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
	0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
	0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, //  . . . . . . . .
	0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0b, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x2d, 0x08, 0x3d, 0x08, 0x20, 0x0a, 0x43, 0x0b, 0x72, 0x0b, 0x6f, 0x0b, 0x73, 0x0b, 0x73, 0x0b, // -.=. .C.r.o.s.s.
	0x2d, 0x0b, 0x70, 0x0b, 0x6c, 0x0b, 0x61, 0x0b, 0x74, 0x0b, 0x66, 0x0b, 0x6f, 0x0b, 0x72, 0x0b, // -.p.l.a.t.f.o.r.
	0x6d, 0x0b, 0x20, 0x0b, 0x72, 0x0b, 0x65, 0x0b, 0x6e, 0x0b, 0x64, 0x0b, 0x65, 0x0b, 0x72, 0x0b, // m. .r.e.n.d.e.r.
	0x69, 0x0b, 0x6e, 0x0b, 0x67, 0x0b, 0x20, 0x0b, 0x6c, 0x0b, 0x69, 0x0b, 0x62, 0x0b, 0x72, 0x0b, // i.n.g. .l.i.b.r.
	0x61, 0x0b, 0x72, 0x0b, 0x79, 0x0b, 0x20, 0x0f, 0x3d, 0x08, 0x2d, 0x08, 0x20, 0x01, 0x20, 0x0f, // a.r.y. .=.-. . .
	0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, //  . . . . . . . .
	0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, //  . . . . . . . .
	0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, //  . . . . . . . .
	0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, //  . . . . . . . .
	0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, 0x20, 0x0a, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
	0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, 0x20, 0x0f, //  . . . . . . . .
};
#endif