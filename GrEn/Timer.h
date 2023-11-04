#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
	double tickMS();
	void reset();
	double tickAndReset();
	double getAverage() const;
	double getTickCount() const;
 
private:
	unsigned int tickCount;
	double average;

	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;
};

