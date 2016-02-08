//
// MainPage.xaml.cpp
// MainPage 类的实现。
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "../../../kissshot/kissshot.h"

using namespace Test_WinRT;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍

KS_USE_CORE_CONTAINER;
KS_USE_COMPONENT;
KS_USE_MATH;

MainPage::MainPage()
{
	InitializeComponent();
	EntityRef e1(new Entity);
	EntityRef e2(new Entity);
	e1->addComponent<Camera>()->setTag(100U);
	auto camera = e1->addComponent<Camera>();
	camera->setLookAt(10.0f, 20.0f, 30.0f);
	e2->addComponent(camera);

	int a = 20;
}
