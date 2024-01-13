#include "TerminalSizeWatcher.h"

TerminalSizeWatcher::TerminalSizeWatcher()
{
	getTerminalSize();
}

void TerminalSizeWatcher::getTerminalSize()
{
	ioctl(0, TIOCGWINSZ, &ws);
	cols = ws.ws_col;
	lines = ws.ws_row;
}

void TerminalSizeWatcher::getDimensions(int *cols, int *lines)
{
	getTerminalSize();
	*cols = this->cols;
	*lines = this->lines;
}
