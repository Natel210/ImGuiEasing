#pragma once
#include "Utility/Time/TimeCounter.h"
#include <chrono>
#include <mutex>
namespace ImGuiEasing
{
	/// <summary> A class for counting how many times a specific period has been repeated. </summary>
	class TimeCounter_Internal : public TimeCounter
	{
	public:
		_NODISCARD const bool Running() const final;
		void Start() final;
		void Start(const std::chrono::milliseconds& interval) final;
		void Start(std::chrono::steady_clock::time_point& startTime) final;
		void Start(const std::chrono::milliseconds& interval, std::chrono::steady_clock::time_point& startTime) final;
		void Restart(std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now()) final;
		void Pause() final;
		void Resume() final;
		_NODISCARD bool IsPause() const final;
		void Stop() final;
		_NODISCARD int Counter() final;
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
		_NODISCARD const std::chrono::steady_clock::time_point LastEndTime() const;
		void LastEndTime(const std::chrono::steady_clock::time_point& lastEndTime);
		_NODISCARD const int Count() const;
		void Count(const int& count);
	public:
		TimeCounter_Internal(const std::string& name);
	private:
		std::string _name;
		bool _run = false;
		bool _pause = false;
		int _count = 0;
		std::chrono::steady_clock::time_point _startTime = std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point _lastEndTime = std::chrono::steady_clock::now();
		std::chrono::milliseconds _interval = std::chrono::milliseconds(1000);
	};
}
