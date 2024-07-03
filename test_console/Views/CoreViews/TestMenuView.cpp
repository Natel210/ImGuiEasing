#include "TestMenuView.h"
#include <Library/imgui/imgui.h>


void TestMenuView::WindowItem()
{
	ImVec2 testSize = ImGui::GetWindowSize();
	_windowTitleBarUiCom->Size(testSize.x, 30.f);
	_windowTitleBarUiCom->Render();
	ImGui::NewLine();
	_fileMenuUiCom->Render();
	ImGui::SameLine();
	_viewMenuUiCom->Render();

}

void TestMenuView::RenderAfter()
{
}

TestMenuView::TestMenuView(const std::string& titleName, std::shared_ptr<TestMainView> main)
	: ImGuiEasing::MenuViewBase(), _main(main)
{
	_windowTitleBarUiCom = std::make_shared<ImGuiEasing::WindowTitleBarUiComponent>(titleName);
	_windowTitleBarUiCom->Color(ImVec4(0.212f, 0.459f, 0.533f, 0.8f));
	//_windowTitleBarUiCom->Size(0.0f, 0.0f);

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
		if (ImGui::MenuItem(view->Name(), NULL, viewShow))
			view->Show(!viewShow);
	};
	_viewMenuUiCom->FillMunuItems([&]() {
		if (_main != nullptr)
		{
			addMenuItem(_main->GetViewBase("MyMenuController"));
			addMenuItem(_main->GetViewBase("MyTimeView"));
			//add menu
		}
	});
	_viewMenuUiCom->Size(100.0f, 30.f);
}
