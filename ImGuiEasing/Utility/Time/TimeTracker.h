#pragma once
#include <chrono>
#include <string>
#include "ImGuiEasing/ImGuiEasingDefine.h"
#pragma warning(disable: 4251)
namespace ImGuiEasing
{
	/// <summary>
	/// Measures a specific number of times and provides an average elapsed value based on this. <para/>
	/// Specialized for FPS or optimization time measurement. <para/>
	/// </summary>
	class IMGUIEASING_API TimeTracker
	{
	public:
		virtual const bool Running() const = 0;
		virtual void Check() = 0;
		_NODISCARD virtual std::chrono::milliseconds GetDuration() = 0;
	public:
		_NODISCARD virtual const std::string Name() const = 0;
		virtual void Name(const std::string& name) = 0;
		/// <summary>
		/// The number of buffers stored<para/>
		/// Stores the specified number of Durations and provides an average<para/>
		/// </summary>
		virtual const unsigned int BufferSize() const = 0;
		/// <summary>
		/// The number of buffers stored<para/>
		/// Stores the specified number of Durations and provides an average<para/>
		/// </summary>
		virtual void BufferSize(const unsigned int& bufferSize) = 0;
	public:
		virtual ~TimeTracker() = default;
	};
#pragma warning(default: 4251)
}