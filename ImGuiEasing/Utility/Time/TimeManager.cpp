#include "TimeManager.h"
#include "Utility/Time/internal/TimeManager_Internal.h"
namespace ImGuiEasing
{

	std::chrono::system_clock::time_point Lucid_TimeManager::GetCurrentSystemTime()
	{
		return TimeManager_Internal::GetCurrentSystemTime();
	}

	std::weak_ptr<StopWatch> Lucid_TimeManager::CreateStopWatch(const std::string& name)
	{
		return TimeManager_Internal::CreateStopWatch(name);
	}

	std::weak_ptr<StopWatch> Lucid_TimeManager::GetStopWatch(const std::string& name)
	{
		return TimeManager_Internal::GetStopWatch(name);
	}

	void Lucid_TimeManager::DelStopWatch(const std::string& name)
	{
		return TimeManager_Internal::DelStopWatch(name);
	}

	std::weak_ptr<TimeCounter> Lucid_TimeManager::CreateTimeCounter(const std::string& name)
	{
		return TimeManager_Internal::CreateTimeCounter(name);
	}

	std::weak_ptr<TimeCounter> Lucid_TimeManager::GetTimeCounter(const std::string& name)
	{
		return TimeManager_Internal::GetTimeCounter(name);
	}

	void Lucid_TimeManager::DelTimeCounter(const std::string& name)
	{
		return TimeManager_Internal::DelTimeCounter(name);
	}

	std::weak_ptr<Timer> Lucid_TimeManager::CreateTimer(const std::string& name)
	{
		return TimeManager_Internal::CreateTimer(name);
	}

	std::weak_ptr<Timer> Lucid_TimeManager::GetTimer(const std::string& name)
	{
		return TimeManager_Internal::GetTimer(name);
	}

	void Lucid_TimeManager::DelTimer(const std::string& name)
	{
		return TimeManager_Internal::DelTimer(name);
	}

	std::weak_ptr<TimeTracker> Lucid_TimeManager::CreateTimeTracker(const std::string& name)
	{
		return TimeManager_Internal::CreateTimeTracker(name);
	}

	std::weak_ptr<TimeTracker> Lucid_TimeManager::GetTimeTracker(const std::string& name)
	{
		return TimeManager_Internal::GetTimeTracker(name);
	}

	void Lucid_TimeManager::DelTimeTracker(const std::string& name)
	{
		return TimeManager_Internal::DelTimeTracker(name);
	}

}
