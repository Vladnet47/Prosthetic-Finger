#include "Timer.h"

Timer::Timer(const int duration) {
	this->set(duration);
}

Timer::~Timer() {}

// Sets timer to given duration starting from given time
void Timer::set(const int duration) {
	this->duration = duration;
	this->stopped = true;
}

// Starts the timer at the specified time
void Timer::start(const unsigned long startTime) {
	this->startTime = startTime;
	this->stopped = false;
}

void Timer::stop() {
	this->stopped = true;
}

// Returns true if timer is elapsed
bool Timer::isElapsed(const unsigned long currentTime) const {
	return !this->stopped && currentTime - this->startTime > (unsigned long) this->duration;
}