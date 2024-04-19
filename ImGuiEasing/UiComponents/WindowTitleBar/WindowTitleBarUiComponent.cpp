#include "WindowTitleBarUiComponent.h"
#include <ImGuiEasing/ImGuiEasingCore.h>
#include <iostream>
namespace ImGuiEasing
{
	constexpr char closeWindowButtonName[] = "X";
	constexpr char restoredWindowButtonName[] = "д▒";
	constexpr char maxWindowButtonName[] = "бр";
	constexpr char minWindowButtonName[] = "_";

	void ImGuiEasing::WindowTitleBarUiComponent::Item()
	{
		ImVec2 uiComponentSize = Size();
		ImVec2 buttonSize = ImVec2(uiComponentSize.y, uiComponentSize.y);
		
		std::string colorWindow = Name() + "_ColorWindow";
		ImGui::PushStyleColor(ImGuiCol_ChildBg, Color());
		ImGui::BeginChild(colorWindow.c_str(), uiComponentSize);
		ImGui::PopStyleColor();

		// 
		int buttonCount = 0;
		if (UseClose() == true)
		{
			ImGui::SameLine(uiComponentSize.x - (buttonSize.x * ++buttonCount));
			// able image button
			if (ImGui::Button(closeWindowButtonName, buttonSize))
			{
				ImGuiEasing::ImGuiEasingCore::WindowClose();
			}
		}
		if (UseMaximize() == true)
		{
			ImGui::SameLine(uiComponentSize.x - (buttonSize.x * ++buttonCount));
			if (_isFullScreen == true)
			{
				// able image button
				if (ImGui::Button(restoredWindowButtonName, buttonSize))
				{
					ImGuiEasing::ImGuiEasingCore::WindowRestored();
					_isFullScreen = false;
				}
			}
			else
			{
				// able image button
				if (ImGui::Button(maxWindowButtonName, buttonSize))
				{
					ImGuiEasing::ImGuiEasingCore::WindowMaximize();
					_isFullScreen = true;
				}
			}
		}
		if (UseMinimize() == true)
		{
			ImGui::SameLine(uiComponentSize.x - (buttonSize.x * ++buttonCount));
			// able image button
			if (ImGui::Button(minWindowButtonName, buttonSize))
			{
				ImGuiEasing::ImGuiEasingCore::WindowMinimize();
			}
		}

		// make title
		const std::string text = Name();
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());

		ImVec2 titleRect;
		titleRect.x = (uiComponentSize.x - textSize.x - (buttonSize.x * ++buttonCount)) * 0.5f;
		titleRect.y = (uiComponentSize.y - textSize.y) * 0.5f;

		ImGui::SetCursorPos(titleRect);
		ImGui::Text("%s", text.c_str());

		DragLogic((buttonSize.x * buttonCount));

		ImGui::EndChild();
	}

	void WindowTitleBarUiComponent::Color(const ImVec4& color)
	{
		_color = color;
	}

	const ImVec4 WindowTitleBarUiComponent::Color() const
	{
		return _color;
	}

	void WindowTitleBarUiComponent::UseMinimize(const bool boolan)
	{
		_useMinimize = boolan;
	}

	const bool WindowTitleBarUiComponent::UseMinimize() const
	{
		return _useMinimize;
	}

	void WindowTitleBarUiComponent::UseMaximize(const bool boolan)
	{
		_useMaximize = boolan;
	}

	const bool WindowTitleBarUiComponent::UseMaximize() const
	{
		return _useMaximize;
	}

	void WindowTitleBarUiComponent::UseClose(const bool boolean)
	{
		_useClose = boolean;
	}

	const bool WindowTitleBarUiComponent::UseClose() const
	{
		return _useClose;
	}

	void WindowTitleBarUiComponent::DragLogic(const float buttonAreaX)
	{

		// drag options
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceNoPreviewTooltip
			| ImGuiDragDropFlags_AcceptNoPreviewTooltip | ImGuiDragDropFlags_AcceptNoDrawDefaultRect | ImGuiDragDropFlags_SourceAllowNullID))
		{
			ImGui::EndDragDropSource();
		}

		std::string colorWindow = Name() + "_ColorWindow";
		// start drag
		if (_isDraggingWindow == false 
			&& ImGui::IsKeyPressed(ImGuiKey_MouseLeft, false) == true)
		{
			ImGuiEasing::ImGuiEasingCore::WindowGetPos(_dragStartWindowPosX, _dragStartWindowPosY);
			ImVec2 curComPos = ImGui::GetWindowPos();
			ImVec2 curComSize = Size();
			ImVec2 calRect = ImVec2(curComPos.x + curComSize.x - buttonAreaX, curComPos.y + curComSize.y);
			if (ImGui::IsMouseHoveringRect(curComPos, ImVec2(curComPos.x + curComSize.x - buttonAreaX, curComPos.y + curComSize.y)) == false)
				return;
			_isDraggingWindow = true;
		}
		// dragging
		if (_isDraggingWindow == true && ImGui::IsMouseDragging(ImGuiMouseButton_Left) == true)
		{
			ImVec2 dragDelta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
			ImGuiEasing::ImGuiEasingCore::WindowSetPos(
				_dragStartWindowPosX + static_cast<int>(dragDelta.x),
				_dragStartWindowPosY + static_cast<int>(dragDelta.y));
		}
		// end drag
		if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) == true && _isDraggingWindow)
		{
			_isDraggingWindow = false;
		}
	}

	ImGuiEasing::WindowTitleBarUiComponent::WindowTitleBarUiComponent(const std::string& name)
		: UiComponentBase(name), 
		_isFullScreen(false),
		_color(ImVec4()), _useMinimize(true), _useMaximize(true), _useClose(true),
		_dragStartWindowPosX(-1), _dragStartWindowPosY(-1), _isDraggingWindow(false)
	{
	}

}