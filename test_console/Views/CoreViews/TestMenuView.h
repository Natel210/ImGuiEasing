#pragma once
#include "Views/CoreViews/MenuViewBase.h"
#include "UiComponents/MenuButton/MenuButtonUiComponent.h"
#include "UiComponents/WindowTitleBar/WindowTitleBarUiComponent.h"

#include "testMainView.h"
class TestMenuView : public ImGuiEasing::MenuViewBase
{
public:
	/// <summary> Is it to operate inside the window?
	/// e.g., childWindow </summary>
	void WindowItem() final;
	/// <summary> Additional tasks after creating the window </summary>
	void RenderAfter() final;
public:
	TestMenuView(const std::string& titleName, std::shared_ptr<TestMainView> main);
private:
	std::shared_ptr<TestMainView> _main;
	std::shared_ptr<ImGuiEasing::WindowTitleBarUiComponent> _windowTitleBarUiCom;
	std::shared_ptr<ImGuiEasing::MenuButtonUiComponent> _fileMenuUiCom;
	std::shared_ptr<ImGuiEasing::MenuButtonUiComponent> _viewMenuUiCom;
};

