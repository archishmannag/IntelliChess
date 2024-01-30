#include "../../include/clock.h"

void Clock::startClock()
{
	whiteTimeInterval = blackTimeInterval = 0;
	currentTurn = isWhiteTurn;
	clockThread = std::thread(&Clock::runClock, this);
}

void Clock::stopClock()
{
	if (isRunning)
		isRunning = false;
	clockThread.join();
}

void Clock::runClock()
{
	while (isRunning)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		std::lock_guard<std::mutex> lock(clockMutex);
		decrementTimeLeft();

		if (currentTurn != isWhiteTurn)
		{
			if (currentTurn)
				whiteTimeInterval += increment;
			else
				blackTimeInterval += increment;
		}
		currentTurn = isWhiteTurn;
	}
}

void Clock::decrementTimeLeft()
{
	if (isWhiteTurn)
	{
		if (whiteTimeInterval > 0)
			whiteTimeInterval--;
		else
			decrementTime();
	}
	else
	{
		if (blackTimeInterval > 0)
			blackTimeInterval--;
		else
			decrementTime();
	}
}

void Clock::decrementTime()
{
	if (isWhiteTurn)
	{
		if (whiteSecond > 0)
			whiteSecond--;
		else
		{
			if (whiteMinute > 0)
			{
				whiteMinute--;
				whiteSecond = 59;
			}
			else
			{
				whiteMinute = 0;
				whiteSecond = 0;
				isRunning = false;
				isWhiteTurn = false;
			}
		}
	}
	else
	{
		if (blackSecond > 0)
			blackSecond--;
		else
		{
			if (blackMinute > 0)
			{
				blackMinute--;
				blackSecond = 59;
			}
			else
			{
				blackMinute = 0;
				blackSecond = 0;
				isRunning = false;
			}
		}
	}
}

int Clock::getWhiteMinute()
{
	return whiteMinute;
}

int Clock::getWhiteSecond()
{
	return whiteSecond;
}

int Clock::getWhiteMilliSecond()
{
	return whiteTimeInterval;
}

int Clock::getBlackMinute()
{
	return blackMinute;
}

int Clock::getBlackSecond()
{
	return blackSecond;
}

int Clock::getBlackMilliSecond()
{
	return blackTimeInterval;
}