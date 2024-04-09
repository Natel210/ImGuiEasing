#include "Timer_Internal.h"
namespace ImGuiEasing
{

	const bool Timer_Internal::Running() const
	{
		return Run();
	}

	void Timer_Internal::Start()
	{
		if (Run() == true)
			return;
		StartTime(std::chrono::steady_clock::now());
		Over(false);
		Run(true);
	}

	void Timer_Internal::Start(const std::chrono::milliseconds& interval)
	{
		if (Run() == true)
			return;
		Interval(interval);
		StartTime(std::chrono::steady_clock::now());
		Over(false);
		Run(true);
	}

	void Timer_Internal::Start(std::chrono::steady_clock::time_point& startTime)
	{
		if (Run() == true)
			return;
		StartTime(startTime);
		Over(false);
		Run(true);
	}

	void Timer_Internal::Start(const std::chrono::milliseconds& interval, std::chrono::steady_clock::time_point& startTime)
	{
		if (Run() == true)
			return;
		Interval(interval);
		StartTime(startTime);
		Over(false);
		Run(true);
	}

	void Timer_Internal::Stop()
	{
		if (Run() == false)
			return;
		Run(false);
	}

	bool Timer_Internal::IsOver()
	{
		if (Run() == false)
			return false;
		if (Over() == true)
			return true;
		auto now = std::chrono::steady_clock::now();
		Over(std::chrono::duration_cast<std::chrono::milliseconds>(now - StartTime()) >= Interval());
		return Over();
	}

	const std::chrono::milliseconds Timer_Internal::Remain()
	{
		if (Run() == false)
			return std::chrono::milliseconds(0);
		auto now = std::chrono::steady_clock::now();
		return Interval() - std::chrono::duration_cast<std::chrono::milliseconds>(now - StartTime());
	}

	const std::string Timer_Internal::Name() const
	{
		std::lock_guard<std::mutex> lock(_nameMutex);
		return _name.c_str();
	}

	void Timer_Internal::Name(const std::string& name)
	{
		std::lock_guard<std::mutex> lock(_nameMutex);
		_name = name;
	}

	const std::chrono::milliseconds Timer_Internal::Interval() const
	{
		std::lock_guard<std::mutex> lock(_intervalMutex);
		return _interval;
	}

	void Timer_Internal::Interval(const std::chrono::milliseconds& interval)
	{
		std::lock_guard<std::mutex> lock(_intervalMutex);
		_interval = interval;
	}

	const bool Timer_Internal::Run() const
	{
		std::lock_guard<std::mutex> lock(_runMutex);
		return _run;
	}

	void Timer_Internal::Run(const bool& run)
	{
		std::lock_guard<std::mutex> lock(_runMutex);
		_run = run;
	}

	const std::chrono::steady_clock::time_point Timer_Internal::StartTime() const
	{
		std::lock_guard<std::mutex> lock(_startMutex);
		return _startTime;
	}

	void Timer_Internal::StartTime(const std::chrono::steady_clock::time_point& startTime)
	{
		std::lock_guard<std::mutex> lock(_startMutex);
		_startTime = startTime;
	}

	const bool Timer_Internal::Over() const
	{
		std::lock_guard<std::mutex> lock(_overMutex);
		return _over;
	}

	void Timer_Internal::Over(const bool& over)
	{
		std::lock_guard<std::mutex> lock(_overMutex);
		_over = over;
	}

	Timer_Internal::Timer_Internal(const std::string& name) : Timer(), _name(name)
	{
	}

}
