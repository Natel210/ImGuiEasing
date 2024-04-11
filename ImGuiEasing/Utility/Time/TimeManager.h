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

#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	/// <summary> A builder for time-related classes. </summary>
	class IMGUIEASING_API Lucid_TimeManager
	{
	public:
		/// <summary> Retrieves the current system time set in the operating system. </summary>
		static std::chrono::system_clock::time_point GetCurrentSystemTime();

		static std::weak_ptr<StopWatch> CreateStopWatch(const std::string& name);
		static std::weak_ptr<StopWatch> GetStopWatch(const std::string& name);
		static void DelStopWatch(const std::string& name);

		static std::weak_ptr<TimeCounter> CreateTimeCounter(const std::string& name);
		static std::weak_ptr<TimeCounter> GetTimeCounter(const std::string& name);
		static void DelTimeCounter(const std::string& name);

		static std::weak_ptr<Timer> CreateTimer(const std::string& name);
		static std::weak_ptr<Timer> GetTimer(const std::string& name);
		static void DelTimer(const std::string& name);

		static std::weak_ptr<TimeTracker> CreateTimeTracker(const std::string& name);
		static std::weak_ptr<TimeTracker> GetTimeTracker(const std::string& name);
		static void DelTimeTracker(const std::string& name);
	};
}
#pragma warning(default: 4251)