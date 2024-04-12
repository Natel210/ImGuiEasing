#include "CurrentClockUIComponent.h"

void CurrentClockUIComponent::Item()
{
    ImGui::SeparatorText("Clock");
    auto frameName = Name() + "_Frame";
    ImGui::BeginChild(frameName.c_str(), ImVec2(), ImGuiChildFlags_Border);
    
    //ImGuiEasing::TimeManager::GetCurrentSystemTime();
    auto nowTime = std::chrono::system_clock::now();
    auto nowTimeSinceEpoch = nowTime.time_since_epoch();
    
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(nowTimeSinceEpoch);
    long long int milliSecCount = milliseconds.count() % 1000;
    
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(nowTimeSinceEpoch);
    std::time_t currentTime = seconds.count();
    std::tm timeInfo;
    localtime_s(&timeInfo, &currentTime);
    ImGui::Text("%04d.%02d.%02d", timeInfo.tm_year +1900, timeInfo.tm_mon, timeInfo.tm_mday);
    ImGui::Text("%02d:%02d:%02d.%03d", timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec, milliSecCount);
    
    
    
    ImGui::EndChild();
}

CurrentClockUIComponent::CurrentClockUIComponent(const std::string& name) : ImGuiEasing::UiComponentBase(name)
{
}
