#include "ViewBase.h"
namespace ImGuiEasing
{

    const std::string ViewBase::Name() const
    {
        std::lock_guard<std::mutex> lock(_nameMutex);
        return _name;
    }

    ImGuiWindowFlags ViewBase::WindowFlags() const
    {
        std::lock_guard<std::mutex> lock(_windowFlagsMutex);
        return _windowFlags;
    }

    void ViewBase::WindowFlags(const ImGuiWindowFlags& windowFlags)
    {
        std::lock_guard<std::mutex> lock(_windowFlagsMutex);
        _windowFlags = windowFlags;
    }

    const bool ViewBase::Show() const
    {
        std::lock_guard<std::mutex> lock(_showMutex);
        return _show;
    }

    void ViewBase::Show(const bool show)
    {
        std::lock_guard<std::mutex> lock(_showMutex);
        _show = show;
    }

    void ViewBase::Render()
    {
        if (Show() == false)
            return;
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowViewport(viewport->ID);
        SetNextWindowOption();
        ApplyCustomStyle();
        bool refShow = Show();
        ImGui::Begin(Name().c_str(), &refShow, WindowFlags());
        Show(refShow);
        UnapplyCustomStyle();
        WindowItem();
        ImGui::End();
        RenderAfter();
    }

    void ViewBase::SetNextWindowOption() {}

    void ViewBase::ApplyCustomStyle() {}

    void ViewBase::UnapplyCustomStyle() {}

    ViewBase::ViewBase(const std::string& name)
        : _name(name),
        _windowFlags(ImGuiWindowFlags_NoCollapse),
        _show(true)
    {}

}