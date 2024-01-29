#include "../../include/clock.h"
#include <iostream>
#include <unistd.h>

Clock::Clock()
{
	increment = 10;
	timeLeft = 999;
	minute = 30;
	second = 0;
}

Clock::~Clock()
{
}

void Clock::decrementTimeLeft()
{
	if (timeLeft <= 0)
	{
		decrementTime();
		timeLeft = 999;
	}
	else
		timeLeft -= increment;
}

void Clock::decrementTime()
{
	if (second == 0)
	{
		second = 59;
		minute--;
	}
	else
	{
		second--;
	}
}

int Clock::getMinute()
{
	return minute;
}

int Clock::getSecond()
{
	return second;
}

int Clock::getMilliSecond()
{
	return timeLeft;
}