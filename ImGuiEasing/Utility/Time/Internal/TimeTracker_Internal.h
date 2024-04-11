#pragma once
#include "Utility/Time/TimeTracker.h"
#include <chrono>
#include <mutex>
#include <deque>
namespace ImGuiEasing
{
	/// <summary>
	/// Measures a specific number of times and provides an average elapsed value based on this. <para/>
	/// Specialized for FPS or optimization time measurement. <para/>
	/// </summary>
	class TimeTracker_Internal : public TimeTracker
	{
	public:
		const bool Running() const final;
		void Check() final;
		std::chrono::milliseconds GetDuration() final;
	public:
		const std::string Name() const final;
		void Name(const std::string& name) final;
		/// <summary>
		/// The number of buffers stored<para/>
		/// Stores the specified number of Durations and provides an average<para/>
		/// </summary>
		const unsigned int BufferSize() const final;
		/// <summary>
		/// The number of buffers stored<para/>
		/// Stores the specified number of Durations and provides an average<para/>
		/// </summary>
		void BufferSize(const unsigned int& bufferSize) final;
	private:
		const bool Run() const;
		void Run(const bool& run);
		const std::chrono::steady_clock::time_point CheckTime() const;
		void CheckTime(const std::chrono::steady_clock::time_point& checkTime);
	public:
		TimeTracker_Internal(const std::string& name);
	private:
		std::string _name = "";
		unsigned int _bufferSize = 1;
		bool _run = false;
		std::chrono::steady_clock::time_point _checkTime = std::chrono::steady_clock::now();
		std::deque<std::chrono::milliseconds> _durationDeque;
	private:
		mutable std::mutex _nameMutex;
		mutable std::mutex _bufferSizeMutex;
		mutable std::mutex _runMutex;
		mutable std::mutex _checkTimeMutex;
		mutable std::mutex _durationDequeMutex;
	};
}