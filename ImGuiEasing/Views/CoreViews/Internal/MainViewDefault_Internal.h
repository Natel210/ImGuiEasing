#pragma once
#include "Views/CoreViews/MainViewBase.h"
#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	// Notting Empty View
	class MainViewDefault_Internal : public MainViewBase
	{
	protected:
		void WindowItem() {}
		void RenderAfter() {}
	public:
		MainViewDefault_Internal() = default;
		virtual ~MainViewDefault_Internal() = default;
	};
}
#pragma warning(default: 4251)