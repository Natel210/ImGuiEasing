#include "MenuController.h"
#include "ImGuiEasing/ImGuiEasingCore.h"
#include "Views/CoreViews/RootView.h"
void MenuController::SetNextWindowOption()
{
}

void MenuController::ApplyCustomStyle()
{
}

void MenuController::UnapplyCustomStyle()
{
}

void MenuController::WindowItem()
{
	auto splitCom = ImGuiEasing::ImGuiEasingCore::GetRootView<ImGuiEasing::RootView>()->SplitViewComponent().lock();
	std::string frameName1 = Name() + "_Frame1";
	ImGui::BeginChild(frameName1.c_str(), ImVec2(200.f, 65.0f), ImGuiChildFlags_None, ImGuiWindowFlags_NoBackground);
	ImGui::SeparatorText("Fold & Open Menu");
	ImGui::BeginChild("TimeTracker", ImVec2(200.f, 36.f), ImGuiChildFlags_Border);
	if (ImGui::Button("fold", ImVec2(80.f, 20.f)))
		splitCom->Fold();
	ImGui::SameLine();
	if (ImGui::Button("open", ImVec2(80.f, 20.f)))
		splitCom->Open();
	ImGui::EndChild();
	ImGui::EndChild();

	std::string frameName2 = Name() + "_Frame2";
	ImGui::BeginChild(frameName2.c_str(), ImVec2(200.f, 83.0f), ImGuiChildFlags_None, ImGuiWindowFlags_NoBackground);
	ImGui::SeparatorText("Menu Dock Dir Move");
	ImGui::BeginChild("MenuDockDirMove", ImVec2(200.f, 60.f), ImGuiChildFlags_Border);
	if (ImGui::Button("dock left", ImVec2(80.f, 20.f)))
		splitCom->SplitDirection(ImGuiDir_Left);
	ImGui::SameLine();
	if (ImGui::Button("dock right", ImVec2(80.f, 20.f)))
		splitCom->SplitDirection(ImGuiDir_Right);
	if (ImGui::Button("dock up", ImVec2(80.f, 20.f)))
		splitCom->SplitDirection(ImGuiDir_Up);
	ImGui::SameLine();
	if (ImGui::Button("dock down", ImVec2(80.f, 20.f)))
		splitCom->SplitDirection(ImGuiDir_Down);
	ImGui::EndChild();
	ImGui::EndChild();

	std::string frameName3 = Name() + "_Frame3";
	ImGui::BeginChild(frameName3.c_str(), ImVec2(200.f, 118.0f), ImGuiChildFlags_None, ImGuiWindowFlags_NoBackground);
	ImGui::SeparatorText("Separator Items");
	ImGui::BeginChild("SeparatorItems", ImVec2(200.f, 95.f), ImGuiChildFlags_Border);
	if (ImGui::Button("Lock", ImVec2(80.f, 20.f)))
		splitCom->SeparatorLock(true);
	ImGui::SameLine();
	if (ImGui::Button("Unlock", ImVec2(80.f, 20.f)))
		splitCom->SeparatorLock(false);
	ImGui::NewLine();
	ImGui::Text("SeparatorSize");
	float separatorSize = splitCom->SeparatorSize();
	if (ImGui::SliderFloat("##slider", &separatorSize, 0.0f, 100.0f))
	{
		splitCom->SeparatorSize(separatorSize);
	}
	ImGui::EndChild();
	ImGui::EndChild();
}

void MenuController::RenderAfter()
{
}

MenuController::MenuController(std::string name) : ImGuiEasing::ViewBase(name)
{
}

MenuController::~MenuController()
{
}
