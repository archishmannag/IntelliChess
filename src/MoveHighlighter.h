#ifndef MOVEHIGHLIGHTER_H
#define MOVEHIGHLIGHTER_H

#include <vector>
#include <cstdint>

typedef struct
{
	uint8_t piece_color;
} square;

class MoveHighlighter
{
private:
	std::vector<std::vector<square>> *board;

public:
	MoveHighlighter(std::vector<std::vector<square>> *b);
	~MoveHighlighter();
	void toggleHighlight(int f, int r);
};

#endif