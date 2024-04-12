#pragma once
#include "ImGuiEasing/UiComponentBase.h"
#include "Utility/Time/TimeTracker.h"
/// <summary>
/// This is a time tracker component.											<para/>
/// Provides a clunky design for Item().										<para/>
/// When modifying the UI contents, refer to the Item() section and inherit it.	<para/>
/// </summary>
class TimeTrackerUIComponent : public ImGuiEasing::UiComponentBase
{
public:
	virtual std::shared_ptr<ImGuiEasing::TimeTracker> TimeTracker() final;
	virtual void TimeTracker(std::shared_ptr<ImGuiEasing::TimeTracker> timeTracker) final;
protected:
	/// <summary> User Custom </summary>
	void Item() final;
public:
	TimeTrackerUIComponent(const std::string& name, std::shared_ptr<ImGuiEasing::TimeTracker> timeTracker = nullptr);
	virtual ~TimeTrackerUIComponent() = default;
private:
	std::shared_ptr<ImGuiEasing::TimeTracker> _timeTracker;
};
