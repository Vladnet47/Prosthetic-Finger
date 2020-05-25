#pragma once

class Timer {
public:
	Timer(const int duration);
	~Timer();
	void set(const int duration);
	void start(const unsigned long startTime);
	void stop();
	bool isElapsed(const unsigned long currentTime) const;

private:
	unsigned long startTime;
	int duration;
	bool stopped;
};