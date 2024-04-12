#include "MenuViewBase.h"
namespace ImGuiEasing
{
	void MenuViewBase::SetNextWindowOption()
	{
		ImGui::SetNextWindowSize(ImVec2(-1.f, -1.f));
	}

	void MenuViewBase::ApplyCustomStyle()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
	}

	void MenuViewBase::UnapplyCustomStyle()
	{
		ImGui::PopStyleVar(3);
	}

	MenuViewBase::MenuViewBase() : ViewBase("MenuView")
	{
		WindowFlags(ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
	}

}
