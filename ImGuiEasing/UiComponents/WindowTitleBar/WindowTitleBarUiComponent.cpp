#include "WindowTitleBarUiComponent.h"
#include <ImGuiEasing/ImGuiEasingCore.h>
#include <iostream>
namespace ImGuiEasing
{
	void ImGuiEasing::WindowTitleBarUiComponent::Item()
	{
		auto size = Size();

		ImVec2 buttonSize = ImVec2(Size().y, Size().y);

		DragLogic();

		




		ImGui::SameLine();
		if (ImGui::Button("Restored", buttonSize))
		{
			ImGuiEasing::ImGuiEasingCore::WindowRestored();
		}
		ImGui::SameLine();
		if (ImGui::Button("Min", buttonSize))
		{
			ImGuiEasing::ImGuiEasingCore::WindowMinimize();
		}
		ImGui::SameLine();
		if (ImGui::Button("Max", buttonSize))
		{
			ImGuiEasing::ImGuiEasingCore::WindowMaximize();
		}
		ImGui::SameLine();
		if (ImGui::Button("Close", buttonSize))
		{
			ImGuiEasing::ImGuiEasingCore::WindowClose();
		}


	}

	void WindowTitleBarUiComponent::DragLogic()
	{
		// no dragging
		if (isDraggingWindow == false)
		{
			// check area
			// col point to rect
			auto curMousePos = ImGui::GetMousePos();
			auto curComPos = ImGui::GetWindowPos();
			auto curComSize = Size();
			float l = curComPos.x;
			float r = curComPos.x + curComSize.x;
			float t = curComPos.y;
			float b = curComPos.y + curComSize.y;
			if (curMousePos.x < l || r < curMousePos.x)
				return;
			else if (curMousePos.y < t || b < curMousePos.y)
				return;
		}

		// drag options
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceNoPreviewTooltip
			| ImGuiDragDropFlags_AcceptNoPreviewTooltip | ImGuiDragDropFlags_AcceptNoDrawDefaultRect))
		{
			ImGui::EndDragDropSource();
		}

		// start drag
		if (isDraggingWindow == false && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
		{
			dragStartMousePos = ImGui::GetMousePos();
			ImGuiEasing::ImGuiEasingCore::WindowGetPos(dragStartWindowPosX, dragStartWindowPosY);
			isDraggingWindow = true;
		}
		// dragging
		if (isDraggingWindow == true && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
		{
			ImVec2 dragDelta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
			ImGuiEasing::ImGuiEasingCore::WindowSetPos(dragStartWindowPosX + static_cast<int>(dragDelta.x),
				dragStartWindowPosY + static_cast<int>(dragDelta.y));
		}
		// end drag
		if (!ImGui::IsMouseDragging(ImGuiMouseButton_Left) && isDraggingWindow)
		{
			isDraggingWindow = false;
		}
	}

	ImGuiEasing::WindowTitleBarUiComponent::WindowTitleBarUiComponent(std::string name)
		: UiComponentBase(name), 
		_isFullScreen(false),
		_useMinimize(true), _useMaximize(true), _useClose(true),
		_dragStartMousePos(ImVec2()), _dragStartWindowPosX(0), _dragStartWindowPosY(0), _isDraggingWindow(false)
	{
	}

}