#include "ComboUiComponent.h"
namespace ImGuiEasing
{
	void ComboUiComponent::Item()
	{
        auto selectedString = SelectedString();
        std::string comboName = "##" + Name(); // No thumbname
        if (ImGui::BeginCombo(comboName.c_str(), selectedString.c_str()))
        {
            for (auto item : _list)
            {
                const bool selected = selectedString.compare(item) == 0;
                if (ImGui::Selectable(item.c_str(), selected))
                    SelectedString(item);
                if (selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
	}

    void ComboUiComponent::ItemList(const std::vector<std::string>& list)
    {
        _list = list;
    }

    std::vector<std::string> ComboUiComponent::ItemList() const
    {
        return _list;
    }

    void ComboUiComponent::SelectedString(const std::string selectedString)
    {
        _selectedString = selectedString;
    }

    std::string ComboUiComponent::SelectedString() const
    {
        return _selectedString;
    }

    ComboUiComponent::ComboUiComponent(std::string name, std::string defaultString)
        : UiComponentBase(name), _selectedString(defaultString)
    {
    }

}