#ifndef TILE_HPP
#define TILE_HPP

#include <PreCompiledHeaders.hpp>

class piece;
class empty_tile;

class tile
{
public:
	static std::shared_ptr<tile> create_tile(int c, std::shared_ptr<piece> p);
	int get_tile_coordinate() const;
	virtual bool is_tile_occupied() const;
	virtual std::shared_ptr<piece> get_piece() const;
	virtual std::string stringify() const;

protected:
	const int tile_coordinate_;

	tile(int c);

private:
	static std::unordered_map<int, std::shared_ptr<empty_tile>> initialize_all_empty_tiles();

	static std::unordered_map<int, std::shared_ptr<empty_tile>> empty_tiles_cache;
};

class empty_tile final : public tile
{
public:
	empty_tile(int c);
	bool is_tile_occupied() const override;
	std::shared_ptr<piece> get_piece() const override;
	std::string stringify() const override;
};

class occupied_tile final : public tile
{
public:
	occupied_tile(int c, std::shared_ptr<piece> p);
	bool is_tile_occupied() const override;
	std::shared_ptr<piece> get_piece() const override;
	std::string stringify() const override;

private:
	std::shared_ptr<piece> piece_on_tile_;
};

#endif // TILE_HPP