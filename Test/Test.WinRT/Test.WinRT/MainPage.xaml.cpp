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

class TestComponent : public kissshot::component::IComponent
{
public:
	void print() {};
};

MainPage::MainPage()
{
	InitializeComponent();
	kissshot::Entity entity;

	entity.addComponent<kissshot::component::IComponent>()->setTag(100);
	entity.addComponent<TestComponent>()->setTag(400);
	entity.addComponent<TestComponent>()->setTag(200);
	entity.addComponent<kissshot::component::IComponent>()->setTag(200);
	entity.addComponent<kissshot::component::IComponent>()->setTag(300);
	entity.addComponent<int>();
	int a = 10;

	auto component = entity.getComponent<TestComponent>();
	component->print();

	a = 30;

	entity.removeComponents<kissshot::component::IComponent>();

	a = 20;
}
