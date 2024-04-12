#include "TimeManager.h"
#include "Utility/Time/internal/TimeManager_Internal.h"
namespace ImGuiEasing
{

	std::chrono::system_clock::time_point TimeManager::GetCurrentSystemTime()
	{
		return TimeManager_Internal::GetCurrentSystemTime();
	}

	std::shared_ptr<ImGuiEasing::StopWatch> TimeManager::CreateStopWatch(const std::string& name)
	{
		return TimeManager_Internal::CreateStopWatch(name);
	}

	std::shared_ptr<ImGuiEasing::StopWatch> TimeManager::GetStopWatch(const std::string& name)
	{
		return TimeManager_Internal::GetStopWatch(name);
	}

	void TimeManager::DelStopWatch(const std::string& name)
	{
		return TimeManager_Internal::DelStopWatch(name);
	}

	std::shared_ptr<ImGuiEasing::TimeCounter> TimeManager::CreateTimeCounter(const std::string& name)
	{
		return TimeManager_Internal::CreateTimeCounter(name);
	}

	std::shared_ptr<ImGuiEasing::TimeCounter> TimeManager::GetTimeCounter(const std::string& name)
	{
		return TimeManager_Internal::GetTimeCounter(name);
	}

	void TimeManager::DelTimeCounter(const std::string& name)
	{
		return TimeManager_Internal::DelTimeCounter(name);
	}

	std::shared_ptr<ImGuiEasing::Timer> TimeManager::CreateTimer(const std::string& name)
	{
		return TimeManager_Internal::CreateTimer(name);
	}

	std::shared_ptr<ImGuiEasing::Timer> TimeManager::GetTimer(const std::string& name)
	{
		return TimeManager_Internal::GetTimer(name);
	}

	void TimeManager::DelTimer(const std::string& name)
	{
		return TimeManager_Internal::DelTimer(name);
	}

	std::shared_ptr<ImGuiEasing::TimeTracker> TimeManager::CreateTimeTracker(const std::string& name)
	{
		return TimeManager_Internal::CreateTimeTracker(name);
	}

	std::shared_ptr<ImGuiEasing::TimeTracker> TimeManager::GetTimeTracker(const std::string& name)
	{
		return TimeManager_Internal::GetTimeTracker(name);
	}

	void TimeManager::DelTimeTracker(const std::string& name)
	{
		return TimeManager_Internal::DelTimeTracker(name);
	}

}
