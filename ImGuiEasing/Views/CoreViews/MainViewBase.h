#pragma once
#include "ImGuiEasing/ViewBase.h"
#include <string>
#include <unordered_map>
#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	/// <summary> Specifies the main window. </summary>
	class IMGUIEASING_API MainViewBase : public ImGuiEasing::ViewBase
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
	protected: // A MainDockSpace that completely surrounds [MainView].
		/// <summary> This function must be used at the beginning of WindowItem 
		/// if docking functionality is to be used. </summary>
		virtual void UseMainDockSpace() final;
		_NODISCARD virtual const std::string MainDockSpaceName() final;
	public:
		virtual bool AddView(std::shared_ptr<ImGuiEasing::ViewBase> view) final;
		virtual bool AddView(const std::string& name, std::shared_ptr<ImGuiEasing::ViewBase> view) final;
		virtual bool DelView(const std::string& name) final;
	public:
		_NODISCARD virtual std::shared_ptr<ViewBase> GetViewBase(const std::string& name) final;
	public:
		template<class _ViewBaseTypeClass>
		_NODISCARD std::shared_ptr<_ViewBaseTypeClass> GetView(const std::string& name)
		{
			auto getView = GetViewBase(name);
			if (getView == nullptr)
				return nullptr;
			auto getCasting = std::dynamic_pointer_cast<_ViewBaseTypeClass>(getView);
			if (getCasting == nullptr)
				return nullptr;
			return getCasting;
		}
	public:
		MainViewBase();
		virtual ~MainViewBase();
	private:
		// To be used for storage only by the superior, they will handle the rest.
		std::unordered_map<std::string, std::shared_ptr<ImGuiEasing::ViewBase>> _viewDic;
	};
}
#pragma warning(default: 4251)