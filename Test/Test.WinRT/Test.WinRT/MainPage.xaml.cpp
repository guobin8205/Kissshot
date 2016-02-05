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


MainPage::MainPage()
{
	InitializeComponent();
	kissshot::core::container::Entity e;
	e.addComponent<kissshot::core::component::IComponent>()->setTag(111);

	auto& owner = e.getComponent<kissshot::core::component::IComponent>()->getOwner();
	int a = 10;

	owner.addComponent<kissshot::core::component::IComponent>()->setTag(222);

	int b = 20;

	owner.removeComponent<kissshot::core::component::IComponent>(222);

	int c = 30;
}
