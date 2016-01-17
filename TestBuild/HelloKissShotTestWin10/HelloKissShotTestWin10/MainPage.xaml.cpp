//
// MainPage.xaml.cpp
// MainPage 类的实现。
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "kissshot.h"

using namespace HelloKissShotTestWin10;

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
	kissshot::math::Vector3 vec({ 10.0f,20.0f,30.0f });
	kissshot::math::Vector3 vec2({ 10.0f,20.0f,30.0f });
	auto temp =kissshot::math::MtxTransform(10, 20, 30);
	vec *= temp;
	int a = 30;
}
