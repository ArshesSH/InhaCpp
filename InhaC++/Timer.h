#pragma once

#include <chrono>

class Timer
{
public:
	Timer()
	{
		last = std::chrono::steady_clock::now();
	}
	float GetTime( )
	{
		const auto old = last;
		last = std::chrono::steady_clock::now();
		const std::chrono::duration<float> frameTime = last - old;
		return frameTime.count();
	}
private:
	std::chrono::steady_clock::time_point last;
};