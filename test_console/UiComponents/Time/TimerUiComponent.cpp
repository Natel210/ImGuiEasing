#include "TimerUiComponent.h"
#include <iostream>
// Retrieves the current timer
std::shared_ptr<ImGuiEasing::Timer> TimerUiComponent::Timer()
{
	return _timer;
}

// Sets a new timer
void TimerUiComponent::Timer(std::shared_ptr<ImGuiEasing::Timer> timer)
{
	_timer = timer;
}

// Gets the maximum count for the timer input text
const int TimerUiComponent::TimerInputTextMaxCount() const
{
	std::lock_guard<std::mutex> lock(_timerInputTextMaxCountMutex);
	return _timerInputTextMaxCount;
}

// Sets the maximum count for the timer input text

void TimerUiComponent::TimerInputTextMaxCount(const int& timerInputTextMaxCount)
{
	std::lock_guard<std::mutex> lock(_timerInputTextMaxCountMutex);
	_timerInputTextMaxCount = timerInputTextMaxCount;
}

// Modify the "Item()" to fit your own format after inheriting. 
// Only the default format is provided here.
void TimerUiComponent::Item()
{
	ImGui::SeparatorText("Timer");
	auto frameName = Name() + "_Frame";
	ImGui::BeginChild(frameName.c_str(), ImVec2(200.0f, -1.0f), ImGuiChildFlags_Border);

	auto tempTimer = Timer();
	int tempTimerInputTextMaxCount = TimerInputTextMaxCount();

	// Set the style for the first child window
	auto firstChildName = Name() + "1";
	ImGui::BeginChild(firstChildName.c_str(), ImVec2(80.0f, -1.0f));
	ImGuiInputTextFlags inputTextFlags = ImGuiInputTextFlags_CharsDecimal;
	std::string inputString;
	if (tempTimer->Running() == false) //  Editable
	{
		inputString = std::to_string(_timer->Interval().count()).c_str();
	}
	else
	{
		inputString = std::to_string(tempTimer->Remain().count());
		inputTextFlags |= ImGuiInputTextFlags_ReadOnly;
	}
	inputString.resize(tempTimerInputTextMaxCount); // fit size
	ImGui::PushItemWidth(-FLT_MIN); // Take up all available remaining space

	char* buf = new char[tempTimerInputTextMaxCount+1];
	memset(buf, 0, sizeof(char) * tempTimerInputTextMaxCount);
	memcpy_s(buf, sizeof(char) * tempTimerInputTextMaxCount, inputString.c_str(), sizeof(char) * inputString.size());
	if (ImGui::InputText("###TimerInputText", buf,
		sizeof(char) * tempTimerInputTextMaxCount, inputTextFlags))
	{
		// Reflect text changes upon input
		try { tempTimer->Interval(std::chrono::milliseconds(std::stoll(buf))); }
		// Conversion failed (invalid input)
		catch (const std::invalid_argument&) {}
		// Conversion failed (out of range)
		catch (const std::out_of_range&) {}
	}
	delete[] buf;



	ImGui::PopItemWidth(); // Restore width settings to default
	if (tempTimer->IsOver())
		ImGui::Text(u8"ÃÊ°úµÊ");
	// Ends the current child window
	ImGui::EndChild();

	// Ensures that the next child window is placed in the same line
	ImGui::SameLine();
	//ImGui::SameLine(0.0f,0.0f);

	// Set the style for the second child window
	auto secondChildName = Name() + "2";
	// Start the second child container
	ImGui::BeginChild(secondChildName.c_str(), ImVec2(-1.0f, -1.0f), ImGuiChildFlags_AutoResizeX);
	ImVec2 getSize = ImGui::GetWindowSize();
	if (ImGui::Button("Start", ImVec2(getSize.x, 0.0f)))
	{
		tempTimer->Start();
	}
	if (ImGui::Button("End",ImVec2(getSize.x,0.0f)))
	{
		tempTimer->Stop();
	}
	// Ends the current child window
	ImGui::EndChild();

	ImGui::EndChild();
}

TimerUiComponent::TimerUiComponent(const std::string& name, std::shared_ptr<ImGuiEasing::Timer> timer, const int& timerInputTextMaxCount)
	: ImGuiEasing::UiComponentBase(name), _timer(timer), _timerInputTextMaxCount(timerInputTextMaxCount)
{
}
