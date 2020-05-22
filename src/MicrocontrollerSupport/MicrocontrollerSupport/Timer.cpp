#include "Timer.h"

Timer::Timer(const unsigned long startTime, const int duration) {
	this->set(startTime, duration);
}

Timer::~Timer() {}

void Timer::set(const unsigned long startTime, const int duration) {
	this->startTime = startTime;
	this->duration = duration;
}

// Just sets timer elapsed to true if unsigned long overflows
bool Timer::isElapsed(const unsigned long currentTime) const {
	return currentTime < this->startTime || currentTime > this->startTime + duration;
}