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
		virtual void Color(const ImVec4& color) final;
		_NODISCARD virtual const ImVec4 Color() const final;
	public:
		virtual void UseMinimize(const bool boolan) final;
		_NODISCARD virtual const bool UseMinimize() const final;
		virtual void UseMaximize(const bool boolan) final;
		_NODISCARD virtual const bool UseMaximize() const final;
		virtual void UseClose(const bool boolean) final;
		_NODISCARD virtual const bool UseClose() const final;
	private:
		void DragLogic(const float buttonAreaX);
	public:
		WindowTitleBarUiComponent(std::string name);
		virtual ~WindowTitleBarUiComponent() = default;
	private:
		bool _isFullScreen = false;
	private: // set options
		ImVec4 _color = ImVec4();
		bool _useMinimize = true;
		bool _useMaximize = true;
		bool _useClose = true;
	private: // window drag member
		int _dragStartWindowPosX = -1;
		int _dragStartWindowPosY = -1;
		bool _isDraggingWindow = false;
	private:
		mutable std::mutex _colorMutex;
		mutable std::mutex _useMinimizeMutex;
		mutable std::mutex _useMaximizeMutex;
		mutable std::mutex _useCloseMutex;
	};
}
#pragma warning(default: 4251)