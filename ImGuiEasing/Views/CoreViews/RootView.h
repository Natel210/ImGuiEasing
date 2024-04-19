#pragma once
#include "ImGuiEasing/ViewBase.h"
#include "Views/CoreViews/MenuViewBase.h"
#include "Views/CoreViews/MainViewBase.h"
#include "UiComponents/SplitView/SplitViewUiComponent.h"
#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	/// <summary> Layer separation by splitting Menu and Main. <para/>
	/// The name of the view corresponding to [menu] must be given as [MenuView]. <para/>
	/// The name of the view corresponding to [main] should be given as [MainView]. <para/>
	/// </summary>
	class IMGUIEASING_API RootView : public ImGuiEasing::ViewBase
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
		void WindowItem() final;
		/// <summary> Additional tasks after creating the window </summary>
		void RenderAfter() final;
	public:
		/// <summary> The name of the view corresponding to [menu] must be given as [MenuView]. </summary>
		virtual void MenuView(std::shared_ptr<ImGuiEasing::MenuViewBase> menu) final;
		/// <summary> The name of the view corresponding to [main] should be given as [MainView].  </summary>
		virtual void MainView(std::shared_ptr<ImGuiEasing::MainViewBase> main) final;
		_NODISCARD virtual std::weak_ptr<ImGuiEasing::MenuViewBase> MenuView() final;
		_NODISCARD virtual std::weak_ptr<ImGuiEasing::MainViewBase> MainView() final;
		_NODISCARD virtual std::weak_ptr<ImGuiEasing::SplitViewUiComponent> SplitViewComponent() final;
	public:
		RootView();
		~RootView();
	private:
		std::shared_ptr<ImGuiEasing::SplitViewUiComponent> _splitViewComponent = nullptr;
		std::shared_ptr<ImGuiEasing::MenuViewBase> _menuView = nullptr;
		std::shared_ptr<ImGuiEasing::MainViewBase> _mainView = nullptr;
	};
}
#pragma warning(default: 4251)