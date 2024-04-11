#include "RootView.h"
#include <Library/imgui/imgui_internal.h>
namespace ImGuiEasing
{
	void RootView::SetNextWindowOption()
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y));
		ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y));
		ImGui::SetNextWindowViewport(viewport->ID);
	}

	void RootView::ApplyCustomStyle()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
	}

	void RootView::UnapplyCustomStyle()
	{
		ImGui::PopStyleVar(3);
	}

	void RootView::WindowItem()
	{
		_splitViewComponent->Render();
	}

	void RootView::RenderAfter()
	{
		_menuView->Render();
		_mainView->Render();
	}

	void RootView::MenuView(std::shared_ptr<ImGuiEasing::MenuViewBase> menu)
	{
		if (menu == nullptr)
			return;
		if (menu->Name().compare("MenuView") != 0)
			return;
		_menuView.reset();
		_menuView = menu;
	}

	void RootView::MainView(std::shared_ptr<ImGuiEasing::MainViewBase> main)
	{
		if (main == nullptr)
			return;
		if (main->Name().compare("MainView") != 0)
			return;
		_mainView.reset();
		_mainView = main;
	}

	std::weak_ptr<ImGuiEasing::MenuViewBase> RootView::MenuView()
	{
		return _menuView;
	}

	std::weak_ptr<ImGuiEasing::MainViewBase> RootView::MainView()
	{
		return _mainView;
	}

	std::weak_ptr<ImGuiEasing::SplitViewUiComponent> RootView::SplitViewComponent()
	{
		return _splitViewComponent;
	}

	RootView::RootView() : ViewBase("RootView")
	{
		WindowFlags(ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus
			| ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);

		_splitViewComponent = std::make_shared<SplitViewUiComponent>(
			"RootSplitView", "RootDockSpace",
			"MenuView", "MainView"
			, ImGuiDockNodeFlags_HiddenTabBar | ImGuiDockNodeFlags_NoTabBar 
			| ImGuiDockNodeFlags_NoDocking, ImGuiDir_::ImGuiDir_Up);
	}

	RootView::RootView(std::string name) : ViewBase(name)
	{
		WindowFlags(ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus
			| ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);

		_splitViewComponent = std::make_shared<SplitViewUiComponent>(
			"RootSplitView", "RootDockSpace",
			"MenuView", "MainView"
			, ImGuiDockNodeFlags_HiddenTabBar | ImGuiDockNodeFlags_NoTabBar
			| ImGuiDockNodeFlags_NoDocking, ImGuiDir_::ImGuiDir_Up);
	}

	RootView::~RootView()
	{
		_splitViewComponent.reset();
		_menuView.reset();
		_mainView.reset();
	}

}