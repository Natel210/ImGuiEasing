#pragma once
#include "ImGuiEasing/UiComponentBase.h"
#include <string>
#include <functional>
#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	/// <summary>
	/// push button pop menu window
	/// </summary>
	class IMGUIEASING_API MenuButtonUiComponent : public ImGuiEasing::UiComponentBase
	{
#pragma region inherited function
	protected:
		/// <summary> Sub-implementation </summary>
		void Item() override;
#pragma endregion
	public:
		/// <summary>When changed func once. calling... </summary>
		void FillMunuItems(std::function<void()> fillMunuItems);
	public:
		MenuButtonUiComponent(std::string name);
	private:
		bool _popupWindowMenu = false;
		std::function<void()> _fillMunuItems = nullptr;
	};

}
#pragma warning(default: 4251)