#pragma once
#include "ImGuiEasing/UiComponentBase.h"
#include "Utility/Time/TimeCounter.h"

/// <summary>
/// This is a time interval counter component.									<para/>
/// Provides a clunky design for Item().										<para/>
/// When modifying the UI contents, refer to the Item() section and inherit it.	<para/>
/// </summary>
class TimeCounterUIComponent : public ImGuiEasing::UiComponentBase
{
public:
	virtual std::shared_ptr<ImGuiEasing::TimeCounter> TimeCounter() final;
	virtual void TimeCounter(std::shared_ptr<ImGuiEasing::TimeCounter> timeTracker) final;
protected:
	/// <summary> User Custom </summary>
	void Item() final;
public:
	TimeCounterUIComponent(const std::string& name, std::shared_ptr<ImGuiEasing::TimeCounter> timeCounter = nullptr);
	virtual ~TimeCounterUIComponent() = default;
private:
	std::shared_ptr<ImGuiEasing::TimeCounter> _timeCounter;
private:
	int _timerInputTextMaxCount = 10;
};
