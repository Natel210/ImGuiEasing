#include "TimeManager_Internal.h"
#include "Utility/Time/Internal/StopWatch_Internal.h"
#include "Utility/Time/Internal/TimeCounter_Internal.h"
#include "Utility/Time/Internal/Timer_Internal.h"
#include "Utility/Time/Internal/TimeTracker_Internal.h"

namespace ImGuiEasing
{
	std::unordered_map<std::string, std::shared_ptr<StopWatch>> TimeManager_Internal::_stopWathDic;
	std::unordered_map<std::string, std::shared_ptr<TimeCounter>> TimeManager_Internal::_timeCounterDic;
	std::unordered_map<std::string, std::shared_ptr<Timer>> TimeManager_Internal::_timerDic;
	std::unordered_map<std::string, std::shared_ptr<TimeTracker>> TimeManager_Internal::_timeTrackerDic;

	std::chrono::system_clock::time_point TimeManager_Internal::GetCurrentSystemTime()
	{
		return std::chrono::system_clock::now();
	}

	std::shared_ptr<StopWatch> TimeManager_Internal::CreateStopWatch(std::string name)
	{
		if (_stopWathDic.count(name) == 0)
			_stopWathDic.insert(std::make_pair(name, std::make_shared<StopWatch_Internal>(name)));
		return _stopWathDic.at(name);
	}

	std::shared_ptr<StopWatch> TimeManager_Internal::GetStopWatch(std::string name)
	{
		if (_stopWathDic.count(name) == 0)
			return nullptr;
		return _stopWathDic.at(name);
	}

	void TimeManager_Internal::DelStopWatch(std::string name)
	{
		if (_stopWathDic.count(name) == 0)
			return;
		_stopWathDic.erase(name);
	}

	std::shared_ptr<TimeCounter> TimeManager_Internal::CreateTimeCounter(std::string name)
	{
		if (_timeCounterDic.count(name) == 0)
			_timeCounterDic.insert(std::make_pair(name, std::make_shared<TimeCounter_Internal>(name)));
		return _timeCounterDic.at(name);
	}

	std::shared_ptr<TimeCounter> TimeManager_Internal::GetTimeCounter(std::string name)
	{
		if (_timeCounterDic.count(name) == 0)
			return nullptr;
		return _timeCounterDic.at(name);
	}

	void TimeManager_Internal::DelTimeCounter(std::string name)
	{
		if (_timeCounterDic.count(name) == 0)
			return;
		_timeCounterDic.erase(name);
	}

	std::shared_ptr<Timer> TimeManager_Internal::CreateTimer(std::string name)
	{
		if (_timerDic.count(name) == 0)
			_timerDic.insert(std::make_pair(name, std::make_shared<Timer_Internal>(name)));
		return _timerDic.at(name);
	}

	std::shared_ptr<Timer> TimeManager_Internal::GetTimer(std::string name)
	{
		if (_timerDic.count(name) == 0)
			return nullptr;
		return _timerDic.at(name);
	}

	void TimeManager_Internal::DelTimer(std::string name)
	{
		if (_timerDic.count(name) == 0)
			return;
		_timerDic.erase(name);
	}

	std::shared_ptr<TimeTracker> TimeManager_Internal::CreateTimeTracker(std::string name)
	{
		if (_timeTrackerDic.count(name) == 0)
			_timeTrackerDic.insert(std::make_pair(name, std::make_shared<TimeTracker_Internal>(name)));
		return _timeTrackerDic.at(name);
	}

	std::shared_ptr<TimeTracker> TimeManager_Internal::GetTimeTracker(std::string name)
	{
		if (_timeTrackerDic.count(name) == 0)
			return nullptr;
		return _timeTrackerDic.at(name);
	}

	void TimeManager_Internal::DelTimeTracker(std::string name)
	{
		if (_timeTrackerDic.count(name) == 0)
			return;
		_timeTrackerDic.erase(name);
	}

}
