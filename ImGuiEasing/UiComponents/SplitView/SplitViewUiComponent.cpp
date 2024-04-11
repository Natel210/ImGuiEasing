#include "SplitViewUiComponent.h"
#include <Library/imgui/imgui_internal.h>
namespace ImGuiEasing
{
#pragma region component specific features
	
	void SplitViewUiComponent::Fold()
	{
		std::unique_lock<std::mutex> lock(_foldMutex);
		// Ensures it operates only once during exchange
		if (_fold == true)
			return;
		_fold = true;
		lock.unlock();
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
		std::unique_lock<std::mutex> lock(_foldMutex);
		// Ensures it operates only once during exchange
		if (_fold == false)
			return;
		_fold = false;
		lock.unlock();
		ResizingNode(Scale());
	}

	void SplitViewUiComponent::Scale(const float scale)
	{
		std::lock_guard<std::mutex> lock(_scaleMutex);
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

		
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4());
		ImGui::DockSpace(_dockSpaceID, ImVec2(0.f,0.f), tempRootDockNodeFlag);
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();

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
		std::lock_guard<std::mutex> lock(_dockSpaceFlagMutex);
		return _dockSpaceFlag;
	}

	void SplitViewUiComponent::DockSpaceFlag(const ImGuiDockNodeFlags& dockSpaceFlag)
	{
		std::lock_guard<std::mutex> lock(_dockSpaceFlagMutex);
		_dockSpaceFlag = dockSpaceFlag;
	}

	ImGuiDir_ SplitViewUiComponent::SplitDirection() const
	{
		std::lock_guard<std::mutex> lock(_splitDirectionMutex);
		return _splitDirection;
	}

	void SplitViewUiComponent::SplitDirection(ImGuiDir_ splitDirection)
	{
		std::unique_lock<std::mutex> lock(_splitDirectionMutex);
		if (_splitDirection == splitDirection)
			return;
		lock.unlock();
		if (IsFold() == false && ImGui::DockBuilderGetNode(FirstNodeID()) != nullptr)
		{
			ImVec2 lastScale = ImGui::DockBuilderGetNode(FirstNodeID())->SizeRef;
			if (SplitDirection() == ImGuiDir_Left || SplitDirection() == ImGuiDir_Right)
				Scale(lastScale.x);
			else if (SplitDirection() == ImGuiDir_Up || SplitDirection() == ImGuiDir_Down)
				Scale(lastScale.y);
		}
		lock.lock();
		_splitDirection = splitDirection;
		lock.unlock();
		Rebuild(true);
	}

	bool SplitViewUiComponent::SeparatorLock() const
	{
		std::unique_lock<std::mutex> lock(_separatorLockMutex);
		return _separatorLock;
	}

	void SplitViewUiComponent::SeparatorLock(bool separatorLock)
	{
		std::unique_lock<std::mutex> lock(_separatorLockMutex);
		_separatorLock = separatorLock;
	}

	bool SplitViewUiComponent::SeparatorHide() const
	{
		std::unique_lock<std::mutex> lock(_separatorHideMutex);
		return _separatorHide;
	}

	void SplitViewUiComponent::SeparatorHide(bool separatorHide)
	{
		std::unique_lock<std::mutex> lock(_separatorHideMutex);
		_separatorHide = separatorHide;
	}

	float SplitViewUiComponent::SeparatorSize() const
	{
		std::unique_lock<std::mutex> lock(_separatorSizeMutex);
		return _separatorSize;
	}

	void SplitViewUiComponent::SeparatorSize(float separatorSize)
	{
		std::unique_lock<std::mutex> lock(_separatorSizeMutex);
		_separatorSize = separatorSize;
	}

	ImGuiID SplitViewUiComponent::RootNodeID() const
	{
		std::lock_guard<std::mutex> lock(_rebuildMutex);
		return _dockSpaceID;
	}

	ImGuiID SplitViewUiComponent::FirstNodeID() const
	{
		std::lock_guard<std::mutex> lock(_rebuildMutex);
		return _firstNodeID;
	}

	ImGuiID SplitViewUiComponent::SecondNodeID() const
	{
		std::lock_guard<std::mutex> lock(_rebuildMutex);
		return _secondNodeID;
	}

	const float SplitViewUiComponent::Scale() const
	{
		std::lock_guard<std::mutex> lock(_scaleMutex);
		return _scale;
	}

	const bool SplitViewUiComponent::IsFold() const
	{
		std::lock_guard<std::mutex> lock(_foldMutex);
		return _fold;
	}

	void SplitViewUiComponent::Rebuild(const bool rebuild)
	{
		std::unique_lock<std::mutex> lock(_rebuildMutex);
		if (_rebuild == rebuild)
			return;
		_rebuild = rebuild;
		lock.unlock();

	}

	const bool SplitViewUiComponent::Rebuild() const
	{
		std::lock_guard<std::mutex> lock(_rebuildMutex);
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
		std::lock_guard<std::mutex> lock(_rebuildMutex);
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
	}
}