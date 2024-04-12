#pragma once
#include <chrono>
#include <string>
#include "ImGuiEasing/ImGuiEasingDefine.h"
#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	/// <summary> Provides the elapsed time from "Start()" to now or until "Stop()" is pressed. (one-time) </summary>
	class IMGUIEASING_API StopWatch
	{
	public:
		_NODISCARD virtual const bool Running() const = 0;
		virtual void Start(std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now()) = 0;
		virtual void Restart(std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now()) = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		_NODISCARD virtual bool IsPause() const = 0;
		virtual void Stop() = 0;
		_NODISCARD virtual std::chrono::milliseconds GetDuration(std::chrono::steady_clock::time_point nowTime = std::chrono::steady_clock::now()) = 0;
	public:
		_NODISCARD virtual const std::string Name() const = 0;
		virtual void Name(const std::string& name) = 0;
	public:
		virtual ~StopWatch() = default;
	};
}
#pragma warning(default: 4251)