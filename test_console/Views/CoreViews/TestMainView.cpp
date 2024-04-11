#include "TestMainView.h"
#include <memory>
#include "testMenuView.h"

void TestMainView::WindowItem()
{
	UseMainDockSpace();
}

void TestMainView::RenderAfter()
{
	ImGui::Begin("test1");
	ImGui::End();
	ImGui::Begin("test2");
	ImGui::End();
	_menuController->Render();
}

TestMainView::TestMainView() : ImGuiEasing::MainViewBase()
{
	_menuController = std::make_shared<MenuController>("MenuController");
	AddView(_menuController);

	//AddView(std::dynamic_pointer_cast<ViewBase>(std::make_shared<TestMenuView>(this)));
}
