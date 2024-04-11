#include "../../../include/engine/board/Tile.hpp"

/* Tile */

Tile::Tile(int coordinate) : tileCoordinate(coordinate){};

std::map<int, EmptyTile> Tile::initializeAllEmptyTiles()
{
	std::map<int, EmptyTile> emptyTileMap;

	for (int i = 0; i < 64; i++)
		emptyTileMap.insert(std::pair<int, EmptyTile>(i, EmptyTile(i)));

	return emptyTileMap;
}

const std::map<int, EmptyTile> Tile::EMPTY_TILES_CACHE = Tile::initializeAllEmptyTiles();

Tile Tile::createTile(const int coordinate, Piece *piece)
{
	if (piece == nullptr)
		return (Tile::EMPTY_TILES_CACHE.at(coordinate));
	else
		return *(new OccupiedTile(coordinate, *piece));
}

/* EmptyTile */

EmptyTile::EmptyTile(const int coordinate) : Tile(coordinate){};

bool EmptyTile::isTileOccupied() const
{
	return false;
}

Piece *EmptyTile::getPiece() const
{
	return nullptr;
}

/* OccupiedTile */

OccupiedTile::OccupiedTile(const int coordinate, Piece piece) : Tile(coordinate), pieceOnTile(piece){};

bool OccupiedTile::isTileOccupied() const
{
	return true;
}

Piece *OccupiedTile::getPiece() const
{
	return &(Piece)(this->pieceOnTile);
}
