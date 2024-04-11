#pragma once
#include <string>
#include <memory>
#include <mutex>
#include <unordered_map>
#include "ImGuiEasing/ImGuiEasingDefine.h"
#include "Utility/Time/StopWatch.h"
#include "Utility/Time/TimeCounter.h"
#include "Utility/Time/Timer.h"
#include "Utility/Time/TimeTracker.h"

namespace ImGuiEasing
{
	/// <summary> A builder for time-related classes. </summary>
	class TimeManager_Internal
	{
	public:
		/// <summary> Retrieves the current system time set in the operating system. </summary>
		static std::chrono::system_clock::time_point GetCurrentSystemTime();

		static std::weak_ptr<StopWatch> CreateStopWatch(std::string name);
		static std::weak_ptr<StopWatch> GetStopWatch(std::string name);
		static void DelStopWatch(std::string name);

		static std::weak_ptr<TimeCounter> CreateTimeCounter(std::string name);
		static std::weak_ptr<TimeCounter> GetTimeCounter(std::string name);
		static void DelTimeCounter(std::string name);

		static std::weak_ptr<Timer> CreateTimer(std::string name);
		static std::weak_ptr<Timer> GetTimer(std::string name);
		static void DelTimer(std::string name);

		static std::weak_ptr<TimeTracker> CreateTimeTracker(std::string name);
		static std::weak_ptr<TimeTracker> GetTimeTracker(std::string name);
		static void DelTimeTracker(std::string name);

	private:
		static std::unordered_map<std::string, std::shared_ptr<StopWatch>> _stopWathDic;
		static std::unordered_map<std::string, std::shared_ptr<TimeCounter>> _timeCounterDic;
		static std::unordered_map<std::string, std::shared_ptr<Timer>> _timerDic;
		static std::unordered_map<std::string, std::shared_ptr<TimeTracker>> _timeTrackerDic;
	private: // mutex
		static std::mutex _stopWathDicMutex;
		static std::mutex _timeCounterDicMutex;
		static std::mutex _timerDicMutex;
		static std::mutex _timeTrackerDicMutex;
	};
}