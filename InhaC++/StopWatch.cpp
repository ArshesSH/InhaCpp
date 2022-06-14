#include "StopWatch.h"

StopWatch::StopWatch()
{
	Start();
}

void StopWatch::Start()
{
	startTime = std::chrono::steady_clock::now();
}

void StopWatch::Stop()
{
	endTime = std::chrono::steady_clock::now();
}
