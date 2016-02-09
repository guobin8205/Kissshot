#include "pch.h"
#include "KSEntry-winrt.h"
#include <bx/platform.h>
#include <bx/thread.h>
#include "../../external/bgfx/include/bgfx/bgfx.h"
#include "../../external/bgfx/include/bgfx/bgfxplatform.h"
#include "../../kissshot.h"
#include "KSEntry.h"

#if BX_PLATFORM_WINRT
using namespace kissshot;

using namespace concurrency;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;

// 主函数仅用于初始化我们的 IFrameworkView 类。
[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
	auto kissshotsrc = ref new KissshotSource();
	CoreApplication::Run(kissshotsrc);
	return 0;
}

IFrameworkView^ KissshotSource::CreateView()
{
	return ref new Entry();
}

Entry::Entry() :
	m_windowClosed(false),
	m_windowVisible(true)
{
}

// 创建 IFrameworkView 时调用的第一个方法。
void Entry::Initialize(CoreApplicationView^ applicationView)
{
	// 注册应用程序生命周期的事件处理程序。此示例包括 Activated，因此我们
	// 可激活 CoreWindow 并开始在窗口上渲染。
	applicationView->Activated +=
		ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &Entry::OnActivated);

	CoreApplication::Suspending +=
		ref new EventHandler<SuspendingEventArgs^>(this, &Entry::OnSuspending);

	CoreApplication::Resuming +=
		ref new EventHandler<Platform::Object^>(this, &Entry::OnResuming);

	// 此时，我们具有访问设备的权限。
	// 我们可创建与设备相关的资源。
}

// 创建(或重新创建) CoreWindow 对象时调用。
void Entry::SetWindow(CoreWindow^ window)
{
	window->SizeChanged += 
		ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &Entry::OnWindowSizeChanged);

	window->VisibilityChanged +=
		ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &Entry::OnVisibilityChanged);

	window->Closed += 
		ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &Entry::OnWindowClosed);

	window->PointerMoved += 
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &Entry::OnPointMoved);

	DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();

	currentDisplayInformation->DpiChanged +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &Entry::OnDpiChanged);

	currentDisplayInformation->OrientationChanged +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &Entry::OnOrientationChanged);

	DisplayInformation::DisplayContentsInvalidated +=
		ref new TypedEventHandler<DisplayInformation^, Object^>(this, &Entry::OnDisplayContentsInvalidated);
	bgfx::winrtSetWindow(reinterpret_cast<IUnknown*>(window));
}

void Entry::OnPointMoved(CoreWindow^ window, PointerEventArgs^ args)
{

}

// 初始化场景资源或加载之前保存的应用程序状态。
void Entry::Load(Platform::String^ entryPoint)
{
}

static int32_t MainThreadFunc(void*)
{
	return ::_main_(0, nullptr);
}

// 将在窗口处于活动状态后调用此方法。
void Entry::Run()
{
	bx::Thread thread;
	thread.init(MainThreadFunc, nullptr);
	while (!m_windowClosed)
	{
		if (m_windowVisible)
		{
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
		}
		else
		{
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
		}
	}
	thread.shutdown();
}

// IFrameworkView 所必需的。
// 终止事件不会导致调用 Uninitialize。如果在应用程序在前台运行时销毁 IFrameworkView
// 类，则将调用该方法。
void Entry::Uninitialize()
{
}

// 应用程序生命周期事件处理程序。

void Entry::OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
{
	// Run() 在 CoreWindow 激活前将不会开始。
	CoreWindow::GetForCurrentThread()->Activate();
}

void Entry::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
	// 在请求延期后异步保存应用程序状态。保留延期
	// 表示应用程序正忙于执行挂起操作。
	// 请注意，延期不是无限期的。在大约五秒后，
	// 将强制应用程序退出。
	SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();
}

void Entry::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
	// 还原在挂起时卸载的任何数据或状态。默认情况下，
	// 在从挂起中恢复时，数据和状态会持续保留。请注意，
	// 如果之前已终止应用程序，则不会发生此事件。

	// 在此处插入代码。
}

// 窗口事件处理程序。

void Entry::OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args)
{
}

void Entry::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
	m_windowVisible = args->Visible;
}

void Entry::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
	m_windowClosed = true;
}

// DisplayInformation 事件处理程序。

void Entry::OnDpiChanged(DisplayInformation^ sender, Object^ args)
{
	// 注意: 在此处检索到的 LogicalDpi 值可能与应用的有效 DPI 不匹配
	// 如果正在针对高分辨率设备对它进行缩放。在 DeviceResources 上设置 DPI 后，
	// 应始终使用 GetDpi 方法进行检索。
	// 有关详细信息，请参阅 DeviceResources.cpp。
}

void Entry::OnOrientationChanged(DisplayInformation^ sender, Object^ args)
{
}

void Entry::OnDisplayContentsInvalidated(DisplayInformation^ sender, Object^ args)
{
}
#endif