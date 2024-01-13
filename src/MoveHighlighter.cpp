#include <vector>

class MoveHighlighter
{
private:
	uint8_t (*board)[8][8];

public:
	MoveHighlighter(u_int8_t (*b)[8][8]) : board(b){};
	~MoveHighlighter();
};
