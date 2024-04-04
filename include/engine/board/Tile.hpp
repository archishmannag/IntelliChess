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
	virtual bool isTileOccupied() const;
	virtual Piece *getPiece() const;
};

class EmptyTile : public Tile
{
public:
	EmptyTile(const int coordinate) : Tile(coordinate){};
	bool isTileOccupied() const override;
	Piece *getPiece() const override;
};

class OccupiedTile : public Tile
{
private:
	const Piece pieceOnTile;

public:
	OccupiedTile(const int coordinate, Piece piece) : Tile(coordinate), pieceOnTile(piece){};
	bool isTileOccupied() const override;
	Piece *getPiece() const override;
};

#endif