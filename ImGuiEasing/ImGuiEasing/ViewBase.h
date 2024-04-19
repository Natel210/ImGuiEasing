#pragma once
#include <string>
#include <mutex>
#include <Library/imgui/imgui.h>
#include "ImGuiEasing/ImGuiEasingDefine.h"
#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	/// <summary> An object that can compose a window. </summary>
	class IMGUIEASING_API ViewBase
	{
	public:
		_NODISCARD virtual const std::string Name() const final;
		_NODISCARD virtual ImGuiWindowFlags WindowFlags() const final;
		virtual void WindowFlags(const ImGuiWindowFlags& windowFlags) final;
		_NODISCARD virtual const bool Show() const final;
		virtual void Show(const bool show) final;
	public:
		virtual void Render() final;
	protected:
		/// <summary> Options like SetNextWindowPos </summary>
		virtual void SetNextWindowOption();
		/// <summary> Begin applying options 
		/// such as PushStyleVar, PushStyleVar </summary>
		virtual void ApplyCustomStyle();
		/// <summary> End applying options like PopStyleVar, PopStyleVar, 
		/// must match the declaration count of ApplyCustomStyle </summary>
		virtual void UnapplyCustomStyle();
	protected:
		/// <summary> Is it to operate inside the window?
		/// e.g., childWindow </summary>
		virtual void WindowItem() = 0;
		/// <summary> Additional tasks after creating the window </summary>
		virtual void RenderAfter() = 0;
	public:
		ViewBase(const std::string& name);
		virtual ~ViewBase() = default;
	private:
		const std::string _name;
		ImGuiWindowFlags _windowFlags = ImGuiWindowFlags_NoCollapse;
		bool _show = true;
	};
}
#pragma warning(default: 4251)