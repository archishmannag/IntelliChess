#ifndef TERMINALSIZEWATCHER_H
#define TERMINALSIZEWATCHER_H

#include <csignal>
#include <sys/ioctl.h>

class TerminalSizeWatcher
{
private:
	int cols = -1, lines = -1;
	struct winsize ws;

	void getTerminalSize();

public:
	TerminalSizeWatcher();
	void getDimensions(int *cols, int *lines);
};

#endif