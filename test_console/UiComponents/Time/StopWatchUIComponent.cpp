#include "StopWatchUIComponent.h"
#include <vector>
std::shared_ptr<ImGuiEasing::StopWatch> StopWatchUIComponent::StopWatch()
{
    return _stopWatch;
}

void StopWatchUIComponent::StopWatch(std::shared_ptr<ImGuiEasing::StopWatch> stopWatch)
{
    _stopWatch = stopWatch;
}

void StopWatchUIComponent::Item()
{
    ImGui::SeparatorText("StopWatch");
    auto frameName = Name() + "_Frame";
    ImGui::BeginChild(frameName.c_str(), ImVec2(), ImGuiChildFlags_Border);
    
    if (ImGui::Button("Run", ImVec2(80.f, 20.f)))
        _stopWatch->Start();
    ImGui::SameLine();
    if (ImGui::Button("Stop", ImVec2(80.f, 20.f)))
        _stopWatch->Stop();

    if (ImGui::Button("Pause", ImVec2(80.f, 20.f)))
        _stopWatch->Pause();
    ImGui::SameLine();
    if (ImGui::Button("Resume", ImVec2(80.f, 20.f)))
        _stopWatch->Resume();

    ImGui::SetNextItemWidth(170.0f);
    _combo->Render();

    auto selected = _combo->SelectedString();
    if (selected.compare("Time") == 0)
        Output_Time();
    else if (selected.compare("sec") == 0)
        Output_Seconds();
    else if (selected.compare("ms") == 0)
        Output_Milliseconds();

    ImGui::EndChild();
}

void StopWatchUIComponent::Output_Time()
{
    ImGui::SetNextItemWidth(200.0f);
    auto duration = _stopWatch->GetDuration().count();
    auto ms = duration % 1000LL;
    auto s = (duration / 1000LL) % 60LL;
    auto m = (duration / (1000LL * 60LL)) % 60LL;
    auto h = (duration / (1000LL * 60LL * 60LL)) % 24LL;
    auto d = duration / (1000LL * 60LL * 60LL * 24LL);
    ImGui::Text("%d(day) %02d:%02d:%02d.%03d" , d, h, m, s, ms);
}

void StopWatchUIComponent::Output_Seconds()
{
    ImGui::SetNextItemWidth(200.0f);
    ImGui::Text("%d(sec)", std::chrono::duration_cast<std::chrono::seconds>(_stopWatch->GetDuration()).count());
}

void StopWatchUIComponent::Output_Milliseconds()
{
    ImGui::SetNextItemWidth(200.0);
    ImGui::Text("%d(ms)", _stopWatch->GetDuration().count());
}

StopWatchUIComponent::StopWatchUIComponent(const std::string& name, std::shared_ptr<ImGuiEasing::StopWatch> stopWatch)
    : UiComponentBase(name), _stopWatch(stopWatch)
{
    std::string comboComName = Name() + "_Combo";
    _combo = std::make_shared<ImGuiEasing::ComboUiComponent>(comboComName, "Time");
    _combo->ItemList({ "Time","sec","ms" });
    _combo->Size(200.0f, 20.0f);
}
