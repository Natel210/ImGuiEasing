#pragma once
#include "Utility/Time/Timer.h"
#include <chrono>
#include <mutex>
#include <string>
namespace ImGuiEasing
{
	/// <summary> A class that indicates whether a certain period has elapsed 
	/// from a specific duration up to a defined cycle. </summary>
	class Timer_Internal : public Timer
	{
	public:
		_NODISCARD const bool Running() const final;
		void Start() final;
		void Start(const std::chrono::milliseconds& interval) final;
		void Start(std::chrono::steady_clock::time_point& startTime) final;
		void Start(const std::chrono::milliseconds& interval, std::chrono::steady_clock::time_point& startTime) final;
		void Stop() final;
		_NODISCARD bool IsOver() final;
		const std::chrono::milliseconds Remain() final;
	public:
		_NODISCARD const std::string Name() const final;
		void Name(const std::string& name) final;
		_NODISCARD const std::chrono::milliseconds Interval() const final;
		void Interval(const std::chrono::milliseconds& interval) final;
	private:
		_NODISCARD const bool Run() const;
		void Run(const bool& run);
		_NODISCARD const std::chrono::steady_clock::time_point StartTime() const;
		void StartTime(const std::chrono::steady_clock::time_point& startTime);
		_NODISCARD const bool Over() const;
		void Over(const bool& over);
	public:
		Timer_Internal(const std::string& name);
	private:
		std::string _name = "";
		bool _run = false;
		bool _over = false;
		std::chrono::steady_clock::time_point _startTime = std::chrono::steady_clock::now();
		std::chrono::milliseconds _interval = std::chrono::milliseconds(1000);
	private: // mutex
		mutable std::mutex _nameMutex;
		mutable std::mutex _runMutex;
		mutable std::mutex _overMutex;
		mutable std::mutex _startMutex;
		mutable std::mutex _intervalMutex;
	};
}
