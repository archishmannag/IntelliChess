#ifndef TILE_HPP
#define TILE_HPP

#include <map>
#include <string>
#include <memory>

class piece;
class empty_tile;

class tile
{
private:
	static std::map<int, std::shared_ptr<empty_tile>> initialize_all_empty_tiles();

	static std::map<int, std::shared_ptr<empty_tile>> empty_tiles_cache;

protected:
	const int tile_coordinate_;

	tile(int c);

public:
	static std::shared_ptr<tile> create_tile(int c, std::shared_ptr<piece> p);
	int get_tile_coordinate() const;
	virtual bool is_tile_occupied() const;
	virtual std::shared_ptr<piece> get_piece() const;
	virtual std::string stringify() const;
};

class empty_tile : public tile
{
public:
	empty_tile(int c);
	bool is_tile_occupied() const override;
	std::shared_ptr<piece> get_piece() const override;
	std::string stringify() const override;
};

class occupied_tile : public tile
{
private:
	std::shared_ptr<piece> piece_on_tile_;

public:
	occupied_tile(int c, std::shared_ptr<piece> p);
	bool is_tile_occupied() const override;
	std::shared_ptr<piece> get_piece() const override;
	std::string stringify() const override;
};

#endif