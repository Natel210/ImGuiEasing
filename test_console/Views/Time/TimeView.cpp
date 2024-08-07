#include "TimeView.h"
#include <format>

#include "Utility/Time/TimeManager.h"
#include "Utility/Time/StopWatch.h"
#include "Utility/Time/TimeCounter.h"
#include "Utility/Time/Timer.h"
#include "Utility/Time/TimeTracker.h"

void TimeItemsView::SetNextWindowOption()
{
}

void TimeItemsView::ApplyCustomStyle()
{
}

void TimeItemsView::UnapplyCustomStyle()
{
}

void TimeItemsView::WindowItem()
{
	_currentClockUIComponent->Render();
	_stopWatchUIComponent->Render();
	_timeCounterUIComponent->Render();
	_timerUiComponent->Render();
	_timeTrackerUIComponent->Render();
}

void TimeItemsView::RenderAfter()
{
}

TimeItemsView::TimeItemsView(const char* name) : ImGuiEasing::ViewBase(name)
{
	std::string viewName = Name();
	auto stopWatch = ImGuiEasing::TimeManager::CreateStopWatch(  viewName + "_StopWatch");
	auto timeCounter = ImGuiEasing::TimeManager::CreateTimeCounter(viewName + "_TimeCounter");
	auto timer = ImGuiEasing::TimeManager::CreateTimer(viewName + "_Timer");
	auto timeTracker = ImGuiEasing::TimeManager::CreateTimeTracker(viewName + "_TimeTracker");
	timeTracker->BufferSize(20);
	{
		//std::format("{}")
		_currentClockUIComponent = std::make_shared<CurrentClockUIComponent>(viewName + "_ClockCom");
		_currentClockUIComponent->Size(200, 80);

		_stopWatchUIComponent = std::make_shared<StopWatchUIComponent>(viewName + "_StopWatchCom", stopWatch);
		_stopWatchUIComponent->Size(200, 130);
		_timeCounterUIComponent = std::make_shared<TimeCounterUIComponent>(viewName + "_TimeCounterCom", timeCounter);
		_timeCounterUIComponent->Size(200, 150);
		_timerUiComponent = std::make_shared<TimerUiComponent>(viewName + "_TimerCom", timer);
		_timerUiComponent->Size(200, 100);
		_timeTrackerUIComponent = std::make_shared<TimeTrackerUIComponent>(viewName + "_TimeTrackerCom", timeTracker);
		_timeTrackerUIComponent->Size(200, 80);
	}

}
