#pragma once
#include "Utility/Time/StopWatch.h"
#include <chrono>
#include <mutex>
namespace ImGuiEasing
{
	/// <summary> Provides the elapsed time from "Start()" to now or until "Stop()" is pressed. (one-time) </summary>
	class StopWatch_Internal : public StopWatch
	{
	public:
		const bool Running() const final;
		void Start(std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now()) final;
		void Restart(std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now()) final;
		void Pause() final;
		void Resume() final;
		bool IsPause() const final;
		void Stop() final;
		std::chrono::milliseconds GetDuration(std::chrono::steady_clock::time_point nowTime = std::chrono::steady_clock::now()) final;
	public:
		const std::string Name() const final;
		void Name(const std::string& name) final;
	private:
		const bool Run() const;
		void Run(const bool& run);
		const std::chrono::steady_clock::time_point StartTime() const;
		void StartTime(const std::chrono::steady_clock::time_point& startTime);
		const std::chrono::steady_clock::time_point LastEndTime() const;
		void LastEndTime(const std::chrono::steady_clock::time_point& lastEndTime);
		const std::chrono::milliseconds Duration() const;
		void Duration(const std::chrono::milliseconds& duration);
	public:
		StopWatch_Internal(const std::string& name);
	private:
		std::string _name = "";
		bool _run = false;
		bool _pause = false;
		std::chrono::steady_clock::time_point _startTime = std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point _lastEndTime = std::chrono::steady_clock::now();
		std::chrono::milliseconds _duration = std::chrono::milliseconds(0);
	private: // mutex
		mutable std::mutex _nameMutex;
		mutable std::mutex _runMutex;
		mutable std::mutex _pauseMutex;
		mutable std::mutex _startMutex;
		mutable std::mutex _lastEndMutex;
		mutable std::mutex _durationMutex;
	};
}
