#include "TimeTrackerUIComponent.h"

std::shared_ptr<ImGuiEasing::TimeTracker> TimeTrackerUIComponent::TimeTracker()
{
	return _timeTracker;
}

void TimeTrackerUIComponent::TimeTracker(std::shared_ptr<ImGuiEasing::TimeTracker> timeTracker)
{
	_timeTracker = timeTracker;
}

void TimeTrackerUIComponent::Item()
{
	ImGui::SeparatorText("TimeTracker");
	auto frameName = Name() + "_Frame";
	ImGui::BeginChild(frameName.c_str(), ImVec2(), ImGuiChildFlags_Border);

	auto ms = _timeTracker->GetDuration().count();
	double fps = 0.0;
	if (ms != 0)
		fps = 1.0 / static_cast<double>(ms) * 1000.0;

	_timeTracker->Check();
	ImGui::BeginChild(Name().c_str());
	ImGui::Text("One Frame : %d(ms)", ms);
	ImGui::Text("FPS : %.3f", fps);
	ImGui::EndChild();

	ImGui::EndChild();
}

TimeTrackerUIComponent::TimeTrackerUIComponent(const std::string& name, std::shared_ptr<ImGuiEasing::TimeTracker> timeTracker)
	: ImGuiEasing::UiComponentBase(name), _timeTracker(timeTracker)
{
}
