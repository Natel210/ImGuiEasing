#pragma once
#include "ImGuiEasing/UiComponentBase.h"
#include <string>
#include <memory>
#include <mutex>
#include "ImGuiEasing/ViewBase.h"
#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	/// <summary> Creates a grid </summary>
	class IMGUIEASING_API SplitViewUiComponent : public UiComponentBase
	{
	// func
	public:
		void Fold();
		void Open();
		void Scale(const float sacle);
	protected:
		/// <summary> Sub-implementation <para/>
		/// This is where the function ends.</summary>
		void Item() final;
	// get set
	public: 
		_NODISCARD virtual const std::string DockSpaceName() const final;
		_NODISCARD virtual const std::string FirstWindowName() const final;
		_NODISCARD virtual const std::string SecondWindowName() const final;
		_NODISCARD virtual ImGuiDockNodeFlags DockSpaceFlag() const final;
		virtual void DockSpaceFlag(const ImGuiDockNodeFlags& dockSpaceFlag) final;
		_NODISCARD virtual ImGuiDir_ SplitDirection() const final;
		virtual void SplitDirection(ImGuiDir_ splitDirection) final;
		_NODISCARD virtual bool SeparatorLock() const final;
		virtual void SeparatorLock(bool separatorLock) final;
		_NODISCARD virtual bool SeparatorHide() const final;
		virtual void SeparatorHide(bool separatorHide) final;
		_NODISCARD virtual float SeparatorSize() const final;
		virtual void SeparatorSize(float separatorSize) final;
	public:
		_NODISCARD virtual ImGuiID RootNodeID() const final;
		_NODISCARD virtual ImGuiID FirstNodeID() const final;
		_NODISCARD virtual ImGuiID SecondNodeID() const final;
	public:
		virtual const float Scale() const final;
	private:
		_NODISCARD virtual const bool IsFold() const final;
		virtual void Rebuild(const bool rebuild) final;
		_NODISCARD virtual const bool Rebuild() const final;
	// internal Logic
	private: 
		/// <summary> Resizes the first node. </summary>
		virtual void ResizingNode(float value) final;
		/// <summary> Reconstructs the DockSpace. </summary>
		virtual void ReBuildDockSpace() final;
	public:
		/// <summary> For splitting, the name of the DockSpace and 
		/// the name of the associated Window. </summary>
		/// <param name="name"> ¢º component name</param>
		/// <param name="dockSpaceName"> ¢º Name of the DockSpace</param>
		/// <param name="firstChildName"> ¢º Name of the window for the first split space</param>
		/// <param name="secondChildName"> ¢º Name of the window for the second split space</param>
		/// <param name="rootDockNodeFlag"> ¢º Flag value for DockSpace</param>
		/// <param name="rootNodeSplittingDirection"> ¢º (Direction for the split)</param>
		SplitViewUiComponent(std::string name,
			std::string dockSpaceName, std::string firstWindowName, std::string secondWindowName,
			ImGuiDockNodeFlags dockSpaceFlag = 0,
			ImGuiDir_ splitDirection = ImGuiDir_::ImGuiDir_Left);

	private: // The part of creating DockSpace and the name of the window that is attached
		const std::string _dockSpaceName;
		const std::string _firstWindowName;
		const std::string _secondWindowName;
		ImGuiDockNodeFlags _dockSpaceFlag = 0;
		ImGuiDir_ _splitDirection = ImGuiDir_::ImGuiDir_Left;
	private: // internal source
		ImGuiID _dockSpaceID = NULL;
		ImGuiID _firstNodeID = NULL;
		ImGuiID _secondNodeID = NULL;
	private:
		bool _rebuild = true;
		bool _fold = false;
		float _scale = 100.0f;
		bool _separatorLock = false;
		bool _separatorHide = false;
		float _separatorSize = 3.f;
	private: // mutex
		mutable std::mutex _dockSpaceFlagMutex;
		mutable std::mutex _splitDirectionMutex;
		mutable std::mutex _rebuildMutex;
		mutable std::mutex _foldMutex;
		mutable std::mutex _scaleMutex;
		mutable std::mutex _separatorLockMutex;
		mutable std::mutex _separatorHideMutex;
		mutable std::mutex _separatorSizeMutex;
	private:
		static constexpr float _foldScale = 0.00000000000001f;
	};
}
#pragma warning(default: 4251)