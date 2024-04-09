#include "UiComponentBase.h"
namespace ImGuiEasing
{

    const std::string UiComponentBase::Name() const
    {
        std::lock_guard<std::mutex> lock(_nameMutex);
        return _name;
    }

    void UiComponentBase::Name(const std::string& name)
    {
        std::lock_guard<std::mutex> lock(_nameMutex);
        _name = name;
    }

    ImGuiWindowFlags UiComponentBase::WindowFlags() const
    {
        std::lock_guard<std::mutex> lock(_windowFlagsMutex);
        return _windowFlags;
    }

    void UiComponentBase::WindowFlags(const ImGuiWindowFlags& windowFlags)
    {
        std::lock_guard<std::mutex> lock(_windowFlagsMutex);
        _windowFlags = windowFlags;
    }

    ImGuiChildFlags UiComponentBase::ChildFlags() const
    {
        std::lock_guard<std::mutex> lock(_childFlagsMutex);
        return _childFlags;
    }

    void UiComponentBase::ChildFlags(const ImGuiChildFlags& childFlags)
    {
        std::lock_guard<std::mutex> lock(_childFlagsMutex);
        _childFlags = childFlags;
    }

    const bool UiComponentBase::Show() const
    {
        std::lock_guard<std::mutex> lock(_showMutex);
        return _show;
    }

    void UiComponentBase::Show(const bool show)
    {
        std::lock_guard<std::mutex> lock(_showMutex);
        _show = show;
    }

    const ImVec2 UiComponentBase::Size() const
    {
        std::lock_guard<std::mutex> lock(_sizeMutex);
        return _size;
    }

    void UiComponentBase::Size(const ImVec2 size)
    {
        std::lock_guard<std::mutex> lock(_sizeMutex);
        _size = size;
    }

    void UiComponentBase::Size(const float x, const float y)
    {
        std::lock_guard<std::mutex> lock(_sizeMutex);
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
        : _name(name), _show(true), _size(ImVec2()),
        _windowFlags(ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground),
        _childFlags(ImGuiChildFlags_None)
    {
    }

}