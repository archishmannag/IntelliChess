#ifndef TILE_HPP
#define TILE_HPP

#include <map>
#include <string>

class Piece;
class EmptyTile;

class Tile
{
private:
	static std::map<int, EmptyTile *> initializeAllEmptyTiles();

	static std::map<int, EmptyTile *> EMPTY_TILES_CACHE;

protected:
	const int tileCoordinate;

	explicit Tile(int coordinate);

public:
	static Tile *createTile(int coordinate, Piece *piece);
	int getTileCoordinate() const;
	virtual bool isTileOccupied() const;
	virtual Piece *getPiece() const;
	virtual std::string stringify() const;
};

class EmptyTile : public Tile
{
public:
	explicit EmptyTile(int coordinate);
	bool isTileOccupied() const override;
	Piece *getPiece() const override;
	std::string stringify() const override;
};

class OccupiedTile : public Tile
{
private:
	Piece *pieceOnTile;

public:
	OccupiedTile(int coordinate, Piece *piece);
	bool isTileOccupied() const override;
	Piece *getPiece() const override;
	std::string stringify() const override;
};

#endif