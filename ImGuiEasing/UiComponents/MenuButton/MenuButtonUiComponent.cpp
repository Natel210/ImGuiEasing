#include "MenuButtonUiComponent.h"
namespace ImGuiEasing
{

	void MenuButtonUiComponent::Item()
	{
		ImVec2 windowSize = ImGui::GetWindowSize();

		if (ImGui::Button(Name().c_str(), windowSize))
			_popupWindowMenu = true;
		if (_popupWindowMenu == true)
		{
			ImVec2 lastItemPos = ImGui::GetItemRectMin();
			ImVec2 lastItemSize = ImGui::GetItemRectSize();
			ImGui::SetNextWindowPos(ImVec2(lastItemPos.x, lastItemPos.y + lastItemSize.y));

			//According to the size of the button
			//ImGui::SetNextWindowSize(ImVec2(lastItemSize.x, -1.0));
			if (ImGui::BeginPopupContextWindow(nullptr, 0))
			{
				if (_fillMunuItems != nullptr)
					_fillMunuItems();
				ImGui::EndPopup();
			}
			else
				_popupWindowMenu = false;
		}
	}

	void MenuButtonUiComponent::FillMunuItems(std::function<void()> fillMunuItems)
	{
		_fillMunuItems = fillMunuItems;
	}

	MenuButtonUiComponent::MenuButtonUiComponent(std::string name) : UiComponentBase(name)
	{
	}

}