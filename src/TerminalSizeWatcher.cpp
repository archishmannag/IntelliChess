#include <csignal>
#include <sys/ioctl.h>

class TerminalSizeWatcher
{
private:
	int cols = -1, lines = -1;
	struct winsize ws;

	void getTerminalSize()
	{
		ioctl(0, TIOCGWINSZ, &ws);
		cols = ws.ws_col;
		lines = ws.ws_row;
	}

public:
	TerminalSizeWatcher()
	{
		getTerminalSize();
	}

	void getDimensions(int *cols, int *lines)
	{
		getTerminalSize();
		*cols = this->cols;
		*lines = this->lines;
	}
};