#pragma once

class Timer {
public:
	Timer(unsigned long startTime, const int duration);
	~Timer();
	void set(unsigned long startTime, const int duration);
	bool isElapsed(const unsigned long currentTime) const;

private:
	unsigned long startTime;
	int duration;
};