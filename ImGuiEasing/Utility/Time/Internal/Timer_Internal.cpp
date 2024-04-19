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
		return _name.c_str();
	}

	void Timer_Internal::Name(const std::string& name)
	{
		_name = name;
	}

	const std::chrono::milliseconds Timer_Internal::Interval() const
	{
		return _interval;
	}

	void Timer_Internal::Interval(const std::chrono::milliseconds& interval)
	{
		_interval = interval;
	}

	const bool Timer_Internal::Run() const
	{
		return _run;
	}

	void Timer_Internal::Run(const bool& run)
	{
		_run = run;
	}

	const std::chrono::steady_clock::time_point Timer_Internal::StartTime() const
	{
		return _startTime;
	}

	void Timer_Internal::StartTime(const std::chrono::steady_clock::time_point& startTime)
	{
		_startTime = startTime;
	}

	const bool Timer_Internal::Over() const
	{
		return _over;
	}

	void Timer_Internal::Over(const bool& over)
	{
		_over = over;
	}

	Timer_Internal::Timer_Internal(const std::string& name) : Timer(), _name(name)
	{
	}

}
