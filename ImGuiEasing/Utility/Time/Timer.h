#pragma once
#include <chrono>
#include <string>
#include "ImGuiEasing/ImGuiEasingDefine.h"
#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	/// <summary> A class that indicates whether a certain period has elapsed 
	/// from a specific duration up to a defined cycle. </summary>
	class IMGUIEASING_API Timer
	{
	public:
		virtual const bool Running() const = 0;
		virtual void Start() = 0;
		virtual void Start(const std::chrono::milliseconds& interval) = 0;
		virtual void Start(std::chrono::steady_clock::time_point& startTime) = 0;
		virtual void Start(const std::chrono::milliseconds& interval, std::chrono::steady_clock::time_point& startTime) = 0;
		virtual void Stop() = 0;
		virtual bool IsOver() = 0;
		virtual const std::chrono::milliseconds Remain() = 0;
	public:
		virtual const std::string Name() const = 0;
		virtual void Name(const std::string& name) = 0;
		virtual const std::chrono::milliseconds Interval() const = 0;
		virtual void Interval(const std::chrono::milliseconds& interval) = 0;
	public:
		virtual ~Timer() = default;
	};
}
#pragma warning(default: 4251)