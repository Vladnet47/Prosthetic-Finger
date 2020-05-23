#include "Timer.h"

Timer::Timer(const unsigned long startTime, const int duration) {
	this->set(startTime, duration);
}

Timer::~Timer() {}

// Sets timer to given duration starting from given time
void Timer::set(const unsigned long startTime, const int duration) {
	this->startTime = startTime;
	this->duration = duration;
}

// Returns true if timer is elapsed
bool Timer::isElapsed(const unsigned long currentTime) const {
	return currentTime - this->startTime > this->duration;
}