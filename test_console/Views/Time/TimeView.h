#pragma once
#include <string>
#include "ImGuiEasing/ViewBase.h"
#include "UiComponents/Time/CurrentClockUIComponent.h"
#include "UiComponents/Time/StopWatchUIComponent.h"
#include "UiComponents/Time/TimeCounterUIComponent.h"
#include "UiComponents/Time/TimerUiComponent.h"
#include "UiComponents/Time/TimeTrackerUIComponent.h"

class TimeItemsView : public ImGuiEasing::ViewBase
{
protected:
	/// <summary> Options like SetNextWindowPos </summary>
	void SetNextWindowOption() override;
	/// <summary> Begin applying options 
	/// such as PushStyleVar, PushStyleVar </summary>
	void ApplyCustomStyle() override;
	/// <summary> End applying options like PopStyleVar, PopStyleVar, 
	/// must match the declaration count of ApplyCustomStyle </summary>
	void UnapplyCustomStyle() override;
protected:
	/// <summary> Is it to operate inside the window?
	/// e.g., childWindow </summary>
	void WindowItem() override;
	/// <summary> Additional tasks after creating the window </summary>
	void RenderAfter() override;
public:
	TimeItemsView(const char* name);
	virtual ~TimeItemsView() = default;
private:
	std::shared_ptr<CurrentClockUIComponent> _currentClockUIComponent;
	std::shared_ptr<StopWatchUIComponent> _stopWatchUIComponent;
	std::shared_ptr<TimeCounterUIComponent> _timeCounterUIComponent;
	std::shared_ptr<TimerUiComponent> _timerUiComponent;
	std::shared_ptr<TimeTrackerUIComponent> _timeTrackerUIComponent;
};

