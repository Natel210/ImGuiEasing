#include "MainViewBase.h"
namespace ImGuiEasing
{
	void MainViewBase::SetNextWindowOption()
	{
	}
	
	void MainViewBase::ApplyCustomStyle()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
	}
	
	void MainViewBase::UnapplyCustomStyle()
	{
		ImGui::PopStyleVar(3);
	}
	
	void MainViewBase::UseMainDockSpace()
	{
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4());
		ImGui::DockSpace(ImGui::GetID("MainDockSpace"), ImVec2(-1.f, -1.f));
		ImGui::PopStyleColor();
	}

	const std::string MainViewBase::MainDockSpaceName()
	{
		return "MainDockSpace";
	}

	bool MainViewBase::AddView(std::shared_ptr<ViewBase> view)
	{
		if (view == nullptr)
			return false;
		if (_viewDic.count(view->Name()) != 0)
			return false;
		_viewDic.insert(std::make_pair(view->Name(), view));
		return true;
	}

	bool MainViewBase::AddView(const std::string& name, std::shared_ptr<ViewBase> view)
	{
		if (view == nullptr)
			return false;
		if (_viewDic.count(name) != 0)
			return false;
		_viewDic.insert(std::make_pair(name, view));
		return true;
	}

	bool MainViewBase::DelView(const std::string& name)
	{
		if (_viewDic.count(name) == 0)
			return false;
		_viewDic.erase(name);
		return true;
	}

	std::shared_ptr<ViewBase> MainViewBase::GetViewBase(const std::string& name)
	{
		if (_viewDic.count(name) == 0)
			return nullptr;
		return _viewDic.at(name);
	}

	MainViewBase::MainViewBase() : ViewBase("MainView")
	{
		WindowFlags(ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
	}

	MainViewBase::~MainViewBase()
	{
		_viewDic.clear();
	}

}