#include <csignal>
#include <sys/ioctl.h>
#include <ncurses.h>
#include <cstring>
#include <unistd.h>

class TerminalSizeWatcher
{
private:
	int &cols, &lines;
	struct winsize window;

	void getTerminalSize()
	{
		ioctl(0, TIOCGWINSZ, &window);
		cols = window.ws_col;
		lines = window.ws_row;
	}

public:
	TerminalSizeWatcher(int &c, int &l) : cols(c), lines(l)
	{
		getTerminalSize();
	}
	~TerminalSizeWatcher() {}
	void checkTerminalSize()
	{
		int newCols = cols, newLines = lines;
		getTerminalSize();
		if (newCols != cols || newLines != lines)
			clear();
	}
};