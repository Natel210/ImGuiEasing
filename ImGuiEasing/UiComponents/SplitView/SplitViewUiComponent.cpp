#include "SplitViewUiComponent.h"
#include <Library/imgui/imgui_internal.h>
namespace ImGuiEasing
{
#pragma region component specific features
	
	void SplitViewUiComponent::Fold()
	{
		// Ensures it operates only once during exchange
		if (_fold == true)
			return;
		_fold = true;
		// Adjusts scale based on the split direction
		if (ImGui::DockBuilderGetNode(FirstNodeID()) != nullptr)
		{
			ImVec2 lastScale = ImGui::DockBuilderGetNode(FirstNodeID())->SizeRef;
			if (SplitDirection() == ImGuiDir_Left || SplitDirection() == ImGuiDir_Right)
				Scale(lastScale.x);
			else if (SplitDirection() == ImGuiDir_Up || SplitDirection() == ImGuiDir_Down)
				Scale(lastScale.y);
		}
		ResizingNode(_foldScale);
	}

	void SplitViewUiComponent::Open()
	{
		// Ensures it operates only once during exchange
		if (_fold == false)
			return;
		_fold = false;
		ResizingNode(Scale());
	}

	void SplitViewUiComponent::Scale(const float scale)
	{
		// Ensures it operates only once during exchange
		if (_scale == scale)
			return;
		_scale = scale;

		if (IsFold() == false)
			ResizingNode(_scale);
	}

#pragma endregion

#pragma region inherited function

	void SplitViewUiComponent::Item()
	{
		// Initializes DockSpace and applies settings
		_dockSpaceID = ImGui::GetID(_dockSpaceName.c_str());
		auto tempRootDockNodeFlag = _dockSpaceFlag;

		bool lockSeparator = IsFold() || SeparatorLock();
		bool hideSeparator = IsFold() || SeparatorHide();

		
		//ImGui::PushStyleColor(ImGuiCol_Separator)

		if (lockSeparator == true)
			tempRootDockNodeFlag |= ImGuiDockNodeFlags_NoResize;
		if (hideSeparator == true)
			ImGui::PushStyleVar(ImGuiStyleVar_DockingSeparatorSize, 0.0f);
		else
			ImGui::PushStyleVar(ImGuiStyleVar_DockingSeparatorSize, SeparatorSize());

		
		ImGui::DockSpace(_dockSpaceID, Size(), tempRootDockNodeFlag);
		ImGui::PopStyleVar();

		if (_rebuild == true)
		{
			ReBuildDockSpace();
			if (_fold == true)
				ResizingNode(_foldScale);
			else
				ResizingNode(Scale());
		}
	}

#pragma endregion

#pragma region get set

	const std::string SplitViewUiComponent::DockSpaceName() const
	{
		return _dockSpaceName;
	}

	const std::string SplitViewUiComponent::FirstWindowName() const
	{
		return _firstWindowName;
	}

	const std::string SplitViewUiComponent::SecondWindowName() const
	{
		return _secondWindowName;
	}

	ImGuiDockNodeFlags SplitViewUiComponent::DockSpaceFlag() const
	{
		return _dockSpaceFlag;
	}

	void SplitViewUiComponent::DockSpaceFlag(const ImGuiDockNodeFlags& dockSpaceFlag)
	{
		_dockSpaceFlag = dockSpaceFlag;
	}

	ImGuiDir_ SplitViewUiComponent::SplitDirection() const
	{
		return _splitDirection;
	}

	void SplitViewUiComponent::SplitDirection(ImGuiDir_ splitDirection)
	{
		if (_splitDirection == splitDirection)
			return;
		if (IsFold() == false && ImGui::DockBuilderGetNode(FirstNodeID()) != nullptr)
		{
			ImVec2 lastScale = ImGui::DockBuilderGetNode(FirstNodeID())->SizeRef;
			if (SplitDirection() == ImGuiDir_Left || SplitDirection() == ImGuiDir_Right)
				Scale(lastScale.x);
			else if (SplitDirection() == ImGuiDir_Up || SplitDirection() == ImGuiDir_Down)
				Scale(lastScale.y);
		}
		_splitDirection = splitDirection;
		Rebuild(true);
	}

	bool SplitViewUiComponent::SeparatorLock() const
	{
		return _separatorLock;
	}

	void SplitViewUiComponent::SeparatorLock(bool separatorLock)
	{
		_separatorLock = separatorLock;
	}

	bool SplitViewUiComponent::SeparatorHide() const
	{
		return _separatorHide;
	}

	void SplitViewUiComponent::SeparatorHide(bool separatorHide)
	{
		_separatorHide = separatorHide;
	}

	float SplitViewUiComponent::SeparatorSize() const
	{
		return _separatorSize;
	}

	void SplitViewUiComponent::SeparatorSize(float separatorSize)
	{
		_separatorSize = separatorSize;
	}

	ImGuiID SplitViewUiComponent::RootNodeID() const
	{
		return _dockSpaceID;
	}

	ImGuiID SplitViewUiComponent::FirstNodeID() const
	{
		return _firstNodeID;
	}

	ImGuiID SplitViewUiComponent::SecondNodeID() const
	{
		return _secondNodeID;
	}

	const float SplitViewUiComponent::Scale() const
	{
		return _scale;
	}

	const bool SplitViewUiComponent::IsFold() const
	{
		return _fold;
	}

	void SplitViewUiComponent::Rebuild(const bool rebuild)
	{
		if (_rebuild == rebuild)
			return;
		_rebuild = rebuild;

	}

	const bool SplitViewUiComponent::Rebuild() const
	{
		return _rebuild;
	}

#pragma endregion

#pragma region internal logic

	void SplitViewUiComponent::ResizingNode(float value)
	{
		auto node = ImGui::DockBuilderGetNode(FirstNodeID());
		if (node == nullptr)
			return;
		if (SplitDirection() == ImGuiDir_Left || SplitDirection() == ImGuiDir_Right)
		{
			node->SizeRef.x = value;
			node->SizeRef.y = 0.0f;
		}
		else if (SplitDirection() == ImGuiDir_Up || SplitDirection() == ImGuiDir_Down)
		{
			node->SizeRef.x = 0.0f;
			node->SizeRef.y = value;
		}
	}

	void SplitViewUiComponent::ReBuildDockSpace()
	{
		if (IsFold() == true) // 펴질떄 까지 대기
			return;
		if (_rebuild == false)
			return;
		if (_dockSpaceID == NULL)
			_dockSpaceID = ImGui::GetID(_dockSpaceName.c_str());
		// 기존 레이아웃 제거
		ImGui::DockBuilderRemoveNode(_dockSpaceID);
		// 새 도크 노드 생성
		ImGui::DockBuilderAddNode(_dockSpaceID, ImGuiDockNodeFlags_DockSpace);
		// 도크 노드 분할
		ImGui::DockBuilderSplitNode(_dockSpaceID,
			_splitDirection, 0.1f,
			&_firstNodeID, &_secondNodeID);
		// 각 도크에 윈도우 배정
		ImGui::DockBuilderDockWindow(_firstWindowName.c_str(), _firstNodeID);
		ImGui::DockBuilderDockWindow(_secondWindowName.c_str(), _secondNodeID);
		// 도킹 구성 완료
		ImGui::DockBuilderFinish(_dockSpaceID);
		_rebuild = false;
	}

#pragma endregion

	SplitViewUiComponent::SplitViewUiComponent(std::string name,
		std::string rootNodeName, std::string firstWindowName, std::string secondWindowName,
		ImGuiDockNodeFlags dockSpaceFlag,
		ImGuiDir_ splitDirection)
		: UiComponentBase(name), _dockSpaceName(rootNodeName),
		_firstWindowName(firstWindowName), _secondWindowName(secondWindowName),
		_dockSpaceFlag(dockSpaceFlag), _splitDirection(splitDirection),
		_dockSpaceID(NULL), _firstNodeID(NULL), _secondNodeID(NULL),
		_rebuild(true), _fold(false), _scale(100.0f)
	{
		WindowFlags(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoFocusOnAppearing |  ImGuiWindowFlags_NoBackground);
	}
}