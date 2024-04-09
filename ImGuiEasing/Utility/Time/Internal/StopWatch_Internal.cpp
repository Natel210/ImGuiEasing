#include "StopWatch_Internal.h"
namespace ImGuiEasing
{
	const bool StopWatch_Internal::Running() const
	{
		return Run();
	}
	
	void StopWatch_Internal::Start(std::chrono::steady_clock::time_point startTime)
	{
		if (Run() == true)
			return;
		StartTime(startTime);
		Duration(std::chrono::milliseconds(0));
		LastEndTime(startTime);
		Run(true);
		std::unique_lock<std::mutex> lock(_pauseMutex);
		_pause = false;
		lock.unlock();
	}

	void StopWatch_Internal::Restart(std::chrono::steady_clock::time_point startTime)
	{
		StartTime(startTime);
		Duration(std::chrono::milliseconds(0));
		LastEndTime(startTime);
		Run(true);
		std::unique_lock<std::mutex> lock(_pauseMutex);
		_pause = false;
		lock.unlock();
	}

	void StopWatch_Internal::Pause()
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

	void StopWatch_Internal::Resume()
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

	bool StopWatch_Internal::IsPause() const
	{
		std::lock_guard<std::mutex> lock(_pauseMutex);
		return _pause;
	}
	
	void StopWatch_Internal::Stop()
	{
		if (Run() == false)
			return;
		if (IsPause() == false)
			LastEndTime(std::chrono::steady_clock::now());
		Run(false);
	}
	
	std::chrono::milliseconds StopWatch_Internal::GetDuration(std::chrono::steady_clock::time_point nowTime)
	{
		if (Run() == true && IsPause() == false)
			Duration(std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - StartTime()));
		else // Pause or Stop
			Duration(std::chrono::duration_cast<std::chrono::milliseconds>(LastEndTime() - StartTime()));
		return Duration();
	}
	
	const std::string StopWatch_Internal::Name() const
	{
		std::lock_guard<std::mutex> lock(_nameMutex);
		return _name;
	}
	
	void StopWatch_Internal::Name(const std::string& name)
	{
		std::lock_guard<std::mutex> lock(_nameMutex);
		_name = name;
	}
	
	const bool StopWatch_Internal::Run() const
	{
		std::lock_guard<std::mutex> lock(_runMutex);
		return _run;
	}
	
	void StopWatch_Internal::Run(const bool& run)
	{
		std::lock_guard<std::mutex> lock(_runMutex);
		_run = run;
	}
	
	const std::chrono::steady_clock::time_point StopWatch_Internal::StartTime() const
	{
		std::lock_guard<std::mutex> lock(_startMutex);
		return _startTime;
	}
	
	void StopWatch_Internal::StartTime(const std::chrono::steady_clock::time_point& startTime)
	{
		std::lock_guard<std::mutex> lock(_startMutex);
		_startTime = startTime;
	}
	
	const std::chrono::steady_clock::time_point StopWatch_Internal::LastEndTime() const
	{
		std::lock_guard<std::mutex> lock(_lastEndMutex);
		return _lastEndTime;
	}

	void StopWatch_Internal::LastEndTime(const std::chrono::steady_clock::time_point& lastEndTime)
	{
		std::lock_guard<std::mutex> lock(_lastEndMutex);
		_lastEndTime = lastEndTime;
	}

	const std::chrono::milliseconds StopWatch_Internal::Duration() const
	{
		std::lock_guard<std::mutex> lock(_durationMutex);
		return _duration;
	}

	void StopWatch_Internal::Duration(const std::chrono::milliseconds& duration)
	{
		std::lock_guard<std::mutex> lock(_durationMutex);
		_duration = duration;
	}

	StopWatch_Internal::StopWatch_Internal(const std::string& name) : _name(name)
	{
	}
}
