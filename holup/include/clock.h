#ifndef CLOCK_H
#define CLOCK_H

#include <thread>
#include <mutex>
#include <chrono>

class Clock
{
private:
	int increment, whiteMinute, whiteSecond, whiteTimeInterval, blackMinute, blackSecond, blackTimeInterval;
	bool isRunning, &isWhiteTurn, currentTurn;
	std::thread clockThread;
	std::mutex clockMutex;

	void decrementTime();
	void decrementTimeLeft();
	void runClock();
	void stopClock();

public:
	Clock(int minute, int second, int intervalIncrease, bool &isWhiteTurn) : whiteMinute(minute), blackMinute(minute), whiteSecond(second), blackSecond(second), increment(intervalIncrease), isRunning(true), isWhiteTurn(isWhiteTurn){};
	Clock(int minute, int second, bool &isWhiteTurn) : whiteMinute(minute), blackMinute(minute), whiteSecond(second), blackSecond(second), increment(0), isRunning(true), isWhiteTurn(isWhiteTurn){};
	~Clock()
	{
		stopClock();
	}
	void startClock();
	int getWhiteMinute();
	int getWhiteSecond();
	int getWhiteMilliSecond();
	int getBlackMinute();
	int getBlackSecond();
	int getBlackMilliSecond();
};

#endif