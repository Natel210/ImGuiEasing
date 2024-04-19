#include "UiComponentBase.h"
namespace ImGuiEasing
{

    const std::string UiComponentBase::Name() const
    {
        return _name;
    }

    void UiComponentBase::Name(const std::string& name)
    {
        _name = name;
    }

    ImGuiWindowFlags UiComponentBase::WindowFlags() const
    {
        return _windowFlags;
    }

    void UiComponentBase::WindowFlags(const ImGuiWindowFlags& windowFlags)
    {
        _windowFlags = windowFlags;
    }

    ImGuiChildFlags UiComponentBase::ChildFlags() const
    {
        return _childFlags;
    }

    void UiComponentBase::ChildFlags(const ImGuiChildFlags& childFlags)
    {
        _childFlags = childFlags;
    }

    const bool UiComponentBase::Show() const
    {
        return _show;
    }

    void UiComponentBase::Show(const bool show)
    {
        _show = show;
    }

    const ImVec2 UiComponentBase::Size() const
    {
        return _size;
    }

    void UiComponentBase::Size(const ImVec2 size)
    {
        _size = size;
    }

    void UiComponentBase::Size(const float x, const float y)
    {
        _size = ImVec2(x, y);
    }

    void UiComponentBase::Render()
    {
        if (Show() == true)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.f);
            ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.f);
            ImGui::BeginChild(Name().c_str(), ImVec2(_size), _childFlags,
                _windowFlags);
            Size(ImGui::GetWindowSize());
            ImGui::PopStyleVar(2);
            Item();
            ImGui::EndChild();
        }
    }

    UiComponentBase::UiComponentBase(const std::string& name)
        : _name(name), _show(true), _size(ImVec2(-1.f,-1.f)),
        _windowFlags(ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground),
        _childFlags(ImGuiChildFlags_None)
    {
    }

}