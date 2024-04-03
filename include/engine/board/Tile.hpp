#ifndef TILE_H
#define TILE_H

#include <map>

#include "../pieces/Piece.hpp"

class Tile
{
private:
	static std::map<int, EmptyTile> initializeAllEmptyTiles();

	const static std::map<int, EmptyTile> EMPTY_TILES_CACHE;

protected:
	const int tileCoordinate;

	Tile(int coordinate) : tileCoordinate(coordinate){};

public:
	static Tile createTile(const int coordinate, Piece *piece);
	virtual bool isTileOccupied();
	virtual Piece *getPiece();
};

class EmptyTile : public Tile
{
private:
	EmptyTile(const int coordinate) : Tile(coordinate){};

public:
	bool isTileOccupied() override;
	Piece *getPiece() override;
};

class OccupiedTile : public Tile
{
private:
	const Piece pieceOnTile;

	OccupiedTile(const int coordinate, Piece piece) : Tile(coordinate), pieceOnTile(piece){};

public:
	bool isTileOccupied() override;
	Piece *getPiece() override;
};

#endif