#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include <Library/imgui/imgui.h>

#include "ImGuiEasing/ImGuiEasingDefine.h"
#include "ImGuiEasing/ImguiEasingError.h"
#include "ImGuiEasing/ViewBase.h"

#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	class IMGUIEASING_API ImGuiEasingCore
	{
	public:
		static ImguiEasingError execution();
		static void ChangeView(std::shared_ptr<ViewBase> rootView);
		static std::shared_ptr<ViewBase> GetRootView_ToViewBase();
		template <typename _viewClass>
		static std::shared_ptr<_viewClass> GetRootView()
		{
			std::shared_ptr<ViewBase> viewBase = GetRootView_ToViewBase();
			return std::reinterpret_pointer_cast<_viewClass>(viewBase);
		}
	public: // SDL2 Func
		static void WindowMaximize();
		static void WindowMinimize();
		static void WindowRestored();
		static void WindowGetPos(int& x, int& y);
		static void WindowSetPos(int x, int y);

		static void WindowClose();
	public: // ImGui Func
		static void ImGuiStyleColorDark();
		static void ImGuiStyleColorClassic();
		static void ImGuiStyleColorLight();
	private:
		ImGuiEasingCore();
		~ImGuiEasingCore();
	private:
		static std::shared_ptr<ViewBase> _rootView;
	};

	template <typename _viewClass>
	static std::shared_ptr<ViewBase> ToViewBase(std::shared_ptr<_viewClass> view) {
		return std::dynamic_pointer_cast<ViewBase>(view);
	}

}
#pragma warning(default: 4251)