#pragma once
#include <memory>
#include <string>

#include "Views/CoreViews/MainViewBase.h"

#include "Views/Menu/MenuController.h"
#include "Views/Time/TimeView.h"

class TestMainView : public ImGuiEasing::MainViewBase
{
public:
	/// <summary> Is it to operate inside the window?
	/// e.g., childWindow </summary>
	void WindowItem() final;
	/// <summary> Additional tasks after creating the window </summary>
	void RenderAfter() final;
public:
	TestMainView();
private:
	std::shared_ptr<MenuController> _menuController;
	std::shared_ptr<TimeItemsView> _timeView;
};

