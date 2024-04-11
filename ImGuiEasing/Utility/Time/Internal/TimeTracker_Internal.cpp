#include "TimeTracker_Internal.h"

namespace ImGuiEasing
{
    const bool TimeTracker_Internal::Running() const
    {
        return Run();
    }

    void TimeTracker_Internal::Check()
    {
        if (Run() == false)
        {
            Run(true);
            CheckTime(std::chrono::steady_clock::now());
            return;
        }
        auto lastCheckTime = CheckTime();
        auto nowTime = std::chrono::steady_clock::now();
        CheckTime(nowTime);
        std::lock_guard<std::mutex> lock(_durationDequeMutex);
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - lastCheckTime);
        _durationDeque.push_back(duration);
        int overCount = static_cast<int>(_durationDeque.size()) - static_cast<int>(_bufferSize);
        if (overCount > 0)
            _durationDeque.erase(_durationDeque.begin(), _durationDeque.begin() + overCount);
    }

    std::chrono::milliseconds TimeTracker_Internal::GetDuration()
    {
        std::lock_guard<std::mutex> lock(_durationDequeMutex);
        if (_durationDeque.empty() == true)
            return std::chrono::milliseconds(0);
        std::chrono::milliseconds sumDuration = std::chrono::milliseconds(0);
        for (auto item : _durationDeque)
            sumDuration += item;
        return sumDuration / _durationDeque.size();
    }

    const std::string TimeTracker_Internal::Name() const
    {
        std::lock_guard<std::mutex> lock(_nameMutex);
        return _name.c_str();
    }

    void TimeTracker_Internal::Name(const std::string& name)
    {
        std::lock_guard<std::mutex> lock(_nameMutex);
        _name = name;
    }

    const unsigned int TimeTracker_Internal::BufferSize() const
    {
        std::lock_guard<std::mutex> lock(_bufferSizeMutex);
        return _bufferSize;
    }

    void TimeTracker_Internal::BufferSize(const unsigned int& bufferSize)
    {
        std::lock_guard<std::mutex> lock(_bufferSizeMutex);
        _bufferSize = bufferSize;
    }

    const bool TimeTracker_Internal::Run() const
    {
        std::lock_guard<std::mutex> lock(_runMutex);
        return _run;
    }

    void TimeTracker_Internal::Run(const bool& run)
    {
        std::lock_guard<std::mutex> lock(_runMutex);
        _run = run;
    }

    const std::chrono::steady_clock::time_point TimeTracker_Internal::CheckTime() const
    {
        std::lock_guard<std::mutex> lock(_checkTimeMutex);
        return _checkTime;
    }

    void TimeTracker_Internal::CheckTime(const std::chrono::steady_clock::time_point& checkTime)
    {
        std::lock_guard<std::mutex> lock(_checkTimeMutex);
        _checkTime = checkTime;
    }

    TimeTracker_Internal::TimeTracker_Internal(const std::string& name) : TimeTracker(), _name(name)
    {
    }

}
