#ifndef CLOCK_H
#define CLOCK_H

#include <thread>
#include <mutex>
#include <chrono>

class Clock
{
private:
	int minute, second, increment, timeLeft;
	void decrementTime();
	void decrementTimeLeft();

public:
	Clock();
	~Clock();
	int getMinute();
	int getSecond();
	int getMilliSecond();
};

#endif