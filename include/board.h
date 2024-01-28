#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cstdint>

typedef union
{
	uint16_t piece_color;
	struct
	{
		uint8_t piece : 6;
		uint8_t isWhitePiece : 1;
		uint8_t isHighlighted : 1;
	};
} tile_t;

#endif