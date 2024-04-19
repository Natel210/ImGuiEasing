#include "TestMainView.h"
#include <memory>
#include "ImGuiEasing/ImGuiEasingCore.h"
#include "testMenuView.h"
#include "Views/Menu/MenuController.h"
#include "Views/Time/TimeView.h"

void TestMainView::WindowItem()
{
	UseMainDockSpace();
}

void TestMainView::RenderAfter()
{
	ImGui::Begin("test1테스트");
	static char buf[21];
	//if (ImGui::InputText("##TimeCounterInputText", buf,
	//	sizeof(char) * 20))
	//{
	//	//// Reflect text changes upon input
	//	//try { _timeCounter->Interval(std::chrono::milliseconds(std::stoll(buf))); }
	//	//// Conversion failed (invalid input)
	//	//catch (const std::invalid_argument&) {}
	//	//// Conversion failed (out of range)
	//	//catch (const std::out_of_range&) {}
	//}

	ImGui::End();
	ImGui::Begin("test2테스트");
	ImGui::End();
	_menuController->Render();
	_timeView->Render();
}

TestMainView::TestMainView() : ImGuiEasing::MainViewBase(),
	_menuController(nullptr), _timeView(nullptr)
{
	{
		_menuController = std::make_shared<MenuController>("MyMenuController");
		AddView(_menuController);

		_timeView = std::make_shared<TimeItemsView>("MyTimeView");
		AddView(_timeView);
	}


	//ImGuiIO imGuiIO = ImGui::GetIO();
	//ImGuiEasing::ImGuiEasingCore::CreateImguiFont("kr1", "C:\\Users\\UBISAM\\AppData\\Local\\Microsoft\\Windows\\Fonts\\D2Coding.ttf", 18.0f, NULL, imGuiIO.Fonts->GetGlyphRangesKorean());
	//ImGuiEasing::ImGuiEasingCore::CreateImguiFont("kr2", "C:\\Users\\UBISAM\\AppData\\Local\\Microsoft\\Windows\\Fonts\\D2Coding.ttf", 18.0f, NULL, imGuiIO.Fonts->GetGlyphRangesKorean());
	//AddView(std::dynamic_pointer_cast<ViewBase>(std::make_shared<TestMenuView>(this)));
}
