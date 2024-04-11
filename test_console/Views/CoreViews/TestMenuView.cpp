#include "TestMenuView.h"
#include <Library/imgui/imgui.h>


void TestMenuView::WindowItem()
{


	_windowTitleBarUiCom->Render();
	ImGui::NewLine();
	_fileMenuUiCom->Render();
	ImGui::SameLine();
	_viewMenuUiCom->Render();

}

void TestMenuView::RenderAfter()
{
}

TestMenuView::TestMenuView(std::shared_ptr<TestMainView> main) : ImGuiEasing::MenuViewBase(), _main(main)
{
	_windowTitleBarUiCom = std::make_shared<ImGuiEasing::WindowTitleBarUiComponent>("TitleBar");
	_windowTitleBarUiCom->Size(0.0f, 30.0f);

	_fileMenuUiCom = std::make_shared<ImGuiEasing::MenuButtonUiComponent>("FileMenu");
	_fileMenuUiCom->FillMunuItems([]() {
		ImGui::ArrowButton(">", ImGuiDir_Right);
		ImGui::Button("2");
		ImGui::SmallButton("3");
		ImGui::Button("4");
		ImGui::SmallButton("5");
	});
	_fileMenuUiCom->Size(100.0f, 30.0f);

	_viewMenuUiCom = std::make_shared<ImGuiEasing::MenuButtonUiComponent>("ViewMenu");
	auto addMenuItem = [](std::weak_ptr<ViewBase> viewWeakPointer) {
		if (viewWeakPointer.expired() == true)
			return;
		auto view = viewWeakPointer.lock();
		bool viewShow = view->Show();
		if (ImGui::MenuItem(view->Name().c_str(), NULL, viewShow))
			view->Show(!viewShow);
	};
	_viewMenuUiCom->FillMunuItems([&]() {
		if (_main != nullptr)
		{
			addMenuItem(_main->GetViewBase("MenuController"));
			addMenuItem(_main->GetViewBase("TimeItems"));
			//add menu
		}
	});
	_viewMenuUiCom->Size(100.0f, 30.f);
}
