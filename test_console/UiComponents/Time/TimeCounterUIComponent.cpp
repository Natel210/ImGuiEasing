#include "TimeCounterUIComponent.h"

std::shared_ptr<ImGuiEasing::TimeCounter> TimeCounterUIComponent::TimeCounter()
{
	return _timeCounter;
}

void TimeCounterUIComponent::TimeCounter(std::shared_ptr<ImGuiEasing::TimeCounter> timeTracker)
{
	_timeCounter = timeTracker;
}

void TimeCounterUIComponent::Item()
{
	ImGui::SeparatorText("TimeCounter");
	auto frameName = Name() + "_Frame";
	ImGui::BeginChild(frameName.c_str(), ImVec2(), ImGuiChildFlags_Border);

    if (ImGui::Button("Run", ImVec2(80.f, 20.f)))
		_timeCounter->Start();
    ImGui::SameLine();
    if (ImGui::Button("Stop", ImVec2(80.f, 20.f)))
		_timeCounter->Stop();

    if (ImGui::Button("Pause", ImVec2(80.f, 20.f)))
		_timeCounter->Pause();
    ImGui::SameLine();
    if (ImGui::Button("Resume", ImVec2(80.f, 20.f)))
		_timeCounter->Resume();


	ImGuiInputTextFlags inputTextFlags = ImGuiInputTextFlags_CharsDecimal;
	std::string inputString = std::to_string(_timeCounter->Interval().count()).c_str();
	if (_timeCounter->Running() == true) //  Editable
		inputTextFlags |= ImGuiInputTextFlags_ReadOnly;
	ImGui::SetNextItemWidth(170.0f);
	
	char buf[21] = { 0, };
	memcpy_s(buf, sizeof(char) * 21, inputString.c_str(), sizeof(char) * inputString.size());
	if (ImGui::InputText("##TimeCounterInputText", buf,
		sizeof(char) * 20, inputTextFlags))
	{
		// Reflect text changes upon input
		try { _timeCounter->Interval(std::chrono::milliseconds(std::stoll(buf))); }
		// Conversion failed (invalid input)
		catch (const std::invalid_argument&) {}
		// Conversion failed (out of range)
		catch (const std::out_of_range&) {}
	}
    ImGui::SetNextItemWidth(170.0f);
	ImGui::Text("Count : %d", _timeCounter->Counter());




	ImGui::EndChild();
}

TimeCounterUIComponent::TimeCounterUIComponent(const std::string& name, std::shared_ptr<ImGuiEasing::TimeCounter> timeCounter)
	: ImGuiEasing::UiComponentBase(name), _timeCounter(timeCounter)
{
}
