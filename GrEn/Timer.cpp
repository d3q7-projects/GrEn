#include "Timer.h"

Timer::Timer()
{
	this->start = std::chrono::high_resolution_clock::now();
	this->end = std::chrono::high_resolution_clock::now();
	this->tickCount = 0;
	this->average = 0;
}

double Timer::tickMS()
{
	this->end = std::chrono::high_resolution_clock::now();
	double elapsedTime = std::chrono::duration<double, std::milli>(this->end - this->start).count();
	this->average = (this->average * this->tickCount + elapsedTime) / (this->tickCount + 1);
	this->tickCount++;
	if (!(this->tickCount % 300))
	{
		this->tickCount = 0;
	}
	return elapsedTime;
}

void Timer::reset()
{
	this->start = std::chrono::high_resolution_clock::now();
}

double Timer::tickAndReset()
{
	const double t = this->tickMS();
	reset();
	return t;
}

double Timer::getAverage() const
{
	return this->average;
}

double Timer::getTickCount() const
{
	return this->tickCount;
}
