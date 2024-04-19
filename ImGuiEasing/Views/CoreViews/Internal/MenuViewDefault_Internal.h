#pragma once
#include "Views/CoreViews/MenuViewBase.h"
namespace ImGuiEasing
{
	// Notting Empty View
	class MenuViewDefault_Internal : public MenuViewBase
	{
	protected:
		void WindowItem() final {}
		void RenderAfter() final {}
	public:
		MenuViewDefault_Internal() = default;
		virtual ~MenuViewDefault_Internal() = default;
	};
}
