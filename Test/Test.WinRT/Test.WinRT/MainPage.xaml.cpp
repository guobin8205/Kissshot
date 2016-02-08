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

KS_USE_COMPONENT;

MainPage::MainPage()
{
	InitializeComponent();
	std::shared_ptr<kissshot::core::container::Entity> e1(new kissshot::core::container::Entity);
	auto i1 = std::shared_ptr<kissshot::core::component::IComponent>(new kissshot::core::component::IComponent());
	auto i2 = std::shared_ptr<kissshot::core::component::IComponent>(new kissshot::core::component::Camera());
	i1->setTag(200);

	{
		e1->addComponent<kissshot::core::component::IComponent>()->setTag(300);
		e1->addComponent(i1);
		e1->addComponent(i2);
	}
	e1 = nullptr;

	int a = 20;
}
