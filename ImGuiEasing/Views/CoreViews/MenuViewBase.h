#pragma once
#include "ImGuiEasing/ViewBase.h"
#include <string>
#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	class IMGUIEASING_API MenuViewBase : public ImGuiEasing::ViewBase
	{
	protected:
		/// <summary> Options like SetNextWindowPos </summary>
		void SetNextWindowOption() final;
		/// <summary> Begin applying options 
		/// such as PushStyleVar, PushStyleVar </summary>
		void ApplyCustomStyle() final;
		/// <summary> End applying options like PopStyleVar, PopStyleVar, 
		/// must match the declaration count of ApplyCustomStyle </summary>
		void UnapplyCustomStyle() final;
	protected:
		/// <summary> Is it to operate inside the window?
		/// e.g., childWindow </summary>
		void WindowItem() override = 0;
		/// <summary> Additional tasks after creating the window </summary>
		void RenderAfter() override = 0;

	public:
		MenuViewBase();
		virtual ~MenuViewBase() = default;
	};
}
#pragma warning(default: 4251)