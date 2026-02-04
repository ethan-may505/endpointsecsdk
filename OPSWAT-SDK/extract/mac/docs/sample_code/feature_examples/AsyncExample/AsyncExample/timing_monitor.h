#pragma once
#include <mutex>

namespace
{
	unsigned long long getTickCount()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
	}
}

class TimingMonitor
{
private:
	unsigned long long* _duration;
	unsigned long long _startTime;
public:
	TimingMonitor() = delete;
	TimingMonitor(const TimingMonitor&) = delete;
	TimingMonitor& operator=(const TimingMonitor&) = delete;
	TimingMonitor(TimingMonitor&&) = delete;
	TimingMonitor& operator=(TimingMonitor&&) = delete;

	explicit TimingMonitor(unsigned long long* duration) : _duration(duration)
	{
		_startTime = getTickCount();
	}

	~TimingMonitor()
	{
		if (_duration != nullptr)
			*_duration = getTickCount() - _startTime;
	}
};