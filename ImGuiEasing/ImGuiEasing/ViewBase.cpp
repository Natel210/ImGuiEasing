#include "ViewBase.h"
namespace ImGuiEasing
{

    const char* ViewBase::Name() const
    {
        return _name;
    }

    ImGuiWindowFlags ViewBase::WindowFlags() const
    {
        return _windowFlags;
    }

    void ViewBase::WindowFlags(const ImGuiWindowFlags& windowFlags)
    {
        _windowFlags = windowFlags;
    }

    const bool ViewBase::Show() const
    {
        return _show;
    }

    void ViewBase::Show(const bool show)
    {
        _show = show;
    }

    void ViewBase::Render()
    {
        bool refShow = Show();
        if (refShow == false)
            return;
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowViewport(viewport->ID);
        SetNextWindowOption();
        ApplyCustomStyle();
        ImGui::Begin(_name, &refShow, WindowFlags());
        Show(refShow);
        UnapplyCustomStyle();
        WindowItem();
        ImGui::End();
        RenderAfter();
    }

    void ViewBase::SetNextWindowOption() {}

    void ViewBase::ApplyCustomStyle() {}

    void ViewBase::UnapplyCustomStyle() {}

    ViewBase::ViewBase(const char* name)
        : _name(name),
        _windowFlags(ImGuiWindowFlags_NoCollapse),
        _show(true)
    {}

}