#pragma once
#include <mutex>
#include "ImGuiEasing/UiComponentBase.h"
#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	class IMGUIEASING_API WindowTitleBarUiComponent : public UiComponentBase
	{
#pragma region inherited function
	protected:
		/// <summary> Sub-implementation </summary>
		void Item() override;
#pragma endregion
	public:
		void UseMinimize(const bool boolan);
		void UseMaximize(const bool boolan);
		void UseClose(const bool boolean);
	private:
		void DragLogic();
	public:
		WindowTitleBarUiComponent(std::string name);
	private:
		bool _isFullScreen = false;
	private:
		bool _useMinimize = true;
		bool _useMaximize = true;
		bool _useClose = true;
	private:

	private:
		ImVec2 _dragStartMousePos;
		int _dragStartWindowPosX;
		int _dragStartWindowPosY;
		bool _isDraggingWindow = false;
	};
}
#pragma warning(default: 4251)