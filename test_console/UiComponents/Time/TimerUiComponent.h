#pragma once
#include "ImGuiEasing/UiComponentBase.h"
#include "Utility/Time/Timer.h"
/// <summary>
/// This is a timer component.													<para/>
/// Provides a clunky design for Item().										<para/>
/// When modifying the UI contents, refer to the Item() section and inherit it.	<para/>
/// </summary>
class TimerUiComponent : public ImGuiEasing::UiComponentBase
{
public:
	virtual std::shared_ptr<ImGuiEasing::Timer> Timer() final;
	virtual void Timer(std::shared_ptr<ImGuiEasing::Timer> timer) final;
	virtual const int TimerInputTextMaxCount() const final;
	virtual void TimerInputTextMaxCount(const int& timerInputTextMaxCount) final;
protected:
	/// <summary> User Custom </summary>
	void Item() final;
public:
	TimerUiComponent(const std::string& name, std::shared_ptr<ImGuiEasing::Timer> timer = nullptr,
		const int& timerInputTextMaxCount = 10);
	virtual ~TimerUiComponent() = default;
private:
	std::shared_ptr<ImGuiEasing::Timer> _timer;
	int _timerInputTextMaxCount = 10;
	
private: // mutex
	mutable std::mutex _timerInputTextMaxCountMutex;
};
