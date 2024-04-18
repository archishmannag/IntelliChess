#include <stdexcept>

#include "../../../include/engine/board/Tile.hpp"

/* Tile */

Tile::Tile(int coordinate) : tileCoordinate(coordinate){};

std::map<int, EmptyTile *> Tile::initializeAllEmptyTiles()
{
	std::map<int, EmptyTile *> emptyTileMap;

	for (int i = 0; i < 64; i++)
		emptyTileMap.insert(std::pair<int, EmptyTile *>(i, new EmptyTile(i)));

	return emptyTileMap;
}

std::map<int, EmptyTile *> Tile::EMPTY_TILES_CACHE = Tile::initializeAllEmptyTiles();

Tile *Tile::createTile(const int coordinate, Piece *piece)
{
	if (piece == nullptr)
		return (Tile::EMPTY_TILES_CACHE.at(coordinate));
	else
		return new OccupiedTile(coordinate, piece);
}

bool Tile::isTileOccupied() const
{
	throw std::logic_error("Not implemented. Use derived class functions.1");
};
Piece *Tile::getPiece() const
{
	throw std::logic_error("Not implemented. Use derived class functions.2");
};
std::string Tile::stringify() const
{
	throw std::logic_error("Not implemented. Use derived class functions.3");
};

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

std::string EmptyTile::stringify() const
{
	return "-";
}

/* OccupiedTile */

OccupiedTile::OccupiedTile(const int coordinate, Piece *piece) : Tile(coordinate), pieceOnTile(piece){};

bool OccupiedTile::isTileOccupied() const
{
	return true;
}

Piece *OccupiedTile::getPiece() const
{
	return this->pieceOnTile;
}

std::string OccupiedTile::stringify() const
{
	if (AllianceUtils::isBlack(this->getPiece()->getPieceAlliance()))
	{
		std::string str = this->getPiece()->stringify();
		for (auto &c : str)
			c = std::tolower(c);
		return str;
	}
	else
		return this->getPiece()->stringify();
}