#pragma once
#include <chrono>
#include <string>
#include "ImGuiEasing/ImGuiEasingDefine.h"
#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	/// <summary> A class for counting how many times a specific period has been repeated. </summary>
	class IMGUIEASING_API TimeCounter
	{
	public:
		virtual const bool Running() const = 0;
		virtual void Start() = 0;
		virtual void Start(const std::chrono::milliseconds& interval) = 0;
		virtual void Start(std::chrono::steady_clock::time_point& startTime) = 0;
		virtual void Start(const std::chrono::milliseconds& interval, std::chrono::steady_clock::time_point& startTime) = 0;
		virtual void Restart(std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now()) = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual bool IsPause() const = 0;
		virtual void Stop() = 0;
		virtual int Counter() = 0;
	public:
		virtual const std::string Name() const = 0;
		virtual void Name(const std::string& name) = 0;
		virtual const std::chrono::milliseconds Interval() const = 0;
		virtual void Interval(const std::chrono::milliseconds& interval) = 0;
	public:
		virtual ~TimeCounter() = default;
	};
}
#pragma warning(default: 4251)