#include "TimeCounter_Internal.h"
namespace ImGuiEasing
{
	const bool TimeCounter_Internal::Running() const
	{
		return Run();
	}

	void TimeCounter_Internal::Start()
	{
		if (Run() == true)
			return;
		StartTime(std::chrono::steady_clock::now());
		LastEndTime(StartTime());
		Count(0);
		Run(true);
		std::unique_lock<std::mutex> lock(_pauseMutex);
		_pause = false;
		lock.unlock();
	}

	void TimeCounter_Internal::Start(const std::chrono::milliseconds& interval)
	{
		if (Run() == true)
			return;
		Interval(interval);
		StartTime(std::chrono::steady_clock::now());
		LastEndTime(StartTime());
		Count(0);
		Run(true);
		std::unique_lock<std::mutex> lock(_pauseMutex);
		_pause = false;
		lock.unlock();
	}

	void TimeCounter_Internal::Start(std::chrono::steady_clock::time_point& startTime)
	{
		if (Run() == true)
			return;
		StartTime(startTime);
		LastEndTime(startTime);
		Count(0);
		Run(true);
		std::unique_lock<std::mutex> lock(_pauseMutex);
		_pause = false;
		lock.unlock();
	}

	void TimeCounter_Internal::Start(const std::chrono::milliseconds& interval, std::chrono::steady_clock::time_point& startTime)
	{
		if (Run() == true)
			return;
		Interval(interval);
		StartTime(startTime);
		LastEndTime(startTime);
		Count(0);
		Run(true);
		std::unique_lock<std::mutex> lock(_pauseMutex);
		_pause = false;
		lock.unlock();
	}

	void TimeCounter_Internal::Restart(std::chrono::steady_clock::time_point startTime)
	{
		StartTime(startTime);
		LastEndTime(startTime);
		Count(0);
		Run(true);
		std::unique_lock<std::mutex> lock(_pauseMutex);
		_pause = false;
		lock.unlock();
	}

	void TimeCounter_Internal::Pause()
	{
		if (Run() == false)
			return;
		if (IsPause() == true)
			return;
		LastEndTime(std::chrono::steady_clock::now());
		std::unique_lock<std::mutex> lock(_pauseMutex);
		_pause = true;
		lock.unlock();
	}

	void TimeCounter_Internal::Resume()
	{
		if (Run() == false)
			return;
		if (IsPause() == false)
			return;
		auto nowTime = std::chrono::steady_clock::now();
		auto elapsed = nowTime - LastEndTime();
		StartTime(StartTime() + elapsed);
		std::unique_lock<std::mutex> lock(_pauseMutex);
		_pause = false;
		lock.unlock();
	}

	bool TimeCounter_Internal::IsPause() const
	{
		std::lock_guard<std::mutex> lock(_pauseMutex);
		return _pause;
	}

	void TimeCounter_Internal::Stop()
	{
		if (Run() == false)
			return;
		LastEndTime(std::chrono::steady_clock::now());
		Run(false);
	}

	int TimeCounter_Internal::Counter()
	{
		std::chrono::milliseconds duration;
		if (Run() == true && IsPause() == false)
		{
			auto now = std::chrono::steady_clock::now();
			duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - StartTime());
		}
		else
			duration = std::chrono::duration_cast<std::chrono::milliseconds>(LastEndTime() - StartTime());
		auto interval = Interval();
		auto result = duration.count() / interval.count();
		Count(static_cast<int>(result));
		return Count();
	}

	const std::string TimeCounter_Internal::Name() const
	{
		std::lock_guard<std::mutex> lock(_nameMutex);
		return _name.c_str();
	}

	void TimeCounter_Internal::Name(const std::string& name)
	{
		std::lock_guard<std::mutex> lock(_nameMutex);
		_name = name;
	}

	const std::chrono::milliseconds TimeCounter_Internal::Interval() const
	{
		std::lock_guard<std::mutex> lock(_intervalMutex);
		return _interval;
	}

	void TimeCounter_Internal::Interval(const std::chrono::milliseconds& interval)
	{
		std::lock_guard<std::mutex> lock(_intervalMutex);
		if (_interval == interval)
			return;
		_interval = interval;
		//Change Interval Reset Count
		StartTime(std::chrono::steady_clock::now());
		LastEndTime(std::chrono::steady_clock::now());
	}

	const bool TimeCounter_Internal::Run() const
	{
		std::lock_guard<std::mutex> lock(_runMutex);
		return _run;
	}

	void TimeCounter_Internal::Run(const bool& run)
	{
		std::lock_guard<std::mutex> lock(_runMutex);
		_run = run;
	}

	const std::chrono::steady_clock::time_point TimeCounter_Internal::StartTime() const
	{
		std::lock_guard<std::mutex> lock(_startMutex);
		return _startTime;
	}

	void TimeCounter_Internal::StartTime(const std::chrono::steady_clock::time_point& startTime)
	{
		std::lock_guard<std::mutex> lock(_startMutex);
		_startTime = startTime;
	}

	const std::chrono::steady_clock::time_point TimeCounter_Internal::LastEndTime() const
	{
		std::lock_guard<std::mutex> lock(_lastEndMutex);
		return _lastEndTime;
	}

	void TimeCounter_Internal::LastEndTime(const std::chrono::steady_clock::time_point& lastEndTime)
	{
		std::lock_guard<std::mutex> lock(_lastEndMutex);
		_lastEndTime = lastEndTime;
	}

	const int TimeCounter_Internal::Count() const
	{
		std::lock_guard<std::mutex> lock(_countMutex);
		return _count;
	}

	void TimeCounter_Internal::Count(const int& count)
	{
		std::lock_guard<std::mutex> lock(_countMutex);
		_count = count;
	}

	TimeCounter_Internal::TimeCounter_Internal(const std::string& name) : TimeCounter(), _name(name)
	{
	}

}
