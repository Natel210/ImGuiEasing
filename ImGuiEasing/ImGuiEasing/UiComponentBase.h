#pragma once
#include <string>
#include <mutex>

#include <Library/imgui/imgui.h>
#include "ImGuiEasing/ImGuiEasingDefine.h"
#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	/// <summary> The object responsible for a certain functionality. <para/>
	/// Make basic configuration in Imgui's "Child Window". <para/> </summary>
	class IMGUIEASING_API UiComponentBase
	{
	public:
		virtual const std::string Name() const final;
		virtual void Name(const std::string& name) final;
		virtual ImGuiWindowFlags WindowFlags() const final;
		virtual void WindowFlags(const ImGuiWindowFlags& windowFlags) final;
		virtual ImGuiChildFlags ChildFlags() const final;
		virtual void ChildFlags(const ImGuiChildFlags& childFlags) final;
		virtual const bool Show() const final;
		virtual void Show(const bool show) final;
		virtual const ImVec2 Size() const final;
		virtual void Size(const ImVec2 size) final;
		virtual void Size(const float x, const float y) final;
	public:
		virtual void Render() final;
	protected:
		/// <summary> Implement the type of item you want. <para/>
		/// Child windows are configured. Please fill in the information inside. <para/> </summary>
		virtual void Item() = 0;
	public:
		UiComponentBase(const std::string& name);
		virtual ~UiComponentBase() = default;
	private:
		std::string _name = "";
		ImGuiWindowFlags _windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;
		ImGuiChildFlags _childFlags = ImGuiChildFlags_None;
		bool _show = true; // def : Show!
		ImVec2 _size;
	private: // mutex
		mutable std::mutex _nameMutex;
		mutable std::mutex _windowFlagsMutex;
		mutable std::mutex _childFlagsMutex;
		mutable std::mutex _showMutex;
		mutable std::mutex _sizeMutex;

	};
}
#pragma warning(default: 4251)