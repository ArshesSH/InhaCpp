#pragma once

#include <chrono>

class StopWatch
{
public:
	enum class TimeUnit
	{
		Second = 1,
		Milli = 1000,
		Micro = 1000000
	};

public:
	StopWatch();
	void Start();
	void Stop();

	template<typename T = double, int U = (int)TimeUnit::Second>
	T GetElapsedTime() const
	{
		const std::chrono::duration<T, std::ratio<1,U>> elapsed = endTime - startTime;
		return elapsed.count();
	}
private:
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point endTime;
};