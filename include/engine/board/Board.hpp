/**
 * @file Board.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief The header file for the board class and the board builder class.
 * @version 1.0.0
 */

#ifndef BOARD_HPP
#define BOARD_HPP

#include "PreCompiledHeaders.hpp"

#include "engine/Alliance.hpp"

// Forward declarations
class move;
class pawn;
class tile;
class piece;
class player;
class white_player;
class black_player;
class board;

/**
 * @class board_builder
 * @brief A helper class used to build an object of the board class. This class is used to set the values of the board object before creating it.
 */
class board_builder
{
public: // Getters
    std::shared_ptr<board> get_previous_board() const;
    alliance get_next_move_maker() const;
    const std::unordered_map<int, std::shared_ptr<piece>> &get_board_config() const;
    std::shared_ptr<pawn> get_en_passant_pawn() const;
    std::shared_ptr<move> get_transition_move() const;
    int get_half_move_clock() const;
    int get_full_move_number() const;
    /**
     * @brief Creates a board with all the set values
     *
     * @return A shared pointer to the created board
     */
    std::shared_ptr<board> build();

public: // Setters
    void set_previous_board(std::shared_ptr<board> pb);
    void set_piece(std::shared_ptr<piece> p);
    void set_en_passant_pawn(std::shared_ptr<pawn> ep);
    void set_move_maker(alliance mm);
    void set_transition_move(std::shared_ptr<move> tm);
    void set_half_move_clock(int hmc);
    void set_full_move_number(int fmn);

private:
    alliance next_move_maker_;                                     ///< The alliance of the next move maker
    std::shared_ptr<board> previous_board_ = nullptr;              ///< The previous board in the move tree
    std::shared_ptr<pawn> en_passant_pawn_ = nullptr;              ///< The en passant pawn
    std::shared_ptr<move> transition_move_ = nullptr;              ///< The move which led to this board
    std::unordered_map<int, std::shared_ptr<piece>> board_config_; ///< The board configuration
    int half_move_clock_ = 0;                                      ///< The half move clock
    int full_move_number_ = 1;                                     ///< The full move number
};

/**
 * @class board
 * @brief A class representing the chess board.
 *
 * @details The board class represents an immutable chess board. It contains the game board, the tiles, pieces and also the players with their moves.
 *
 */
class board : public std::enable_shared_from_this<board>
{
public: // Getters
    std::shared_ptr<board> get_previous_board() const;
    std::shared_ptr<tile> get_tile(int tc) const;
    int get_half_move_clock() const;
    int get_full_move_number() const;
    std::shared_ptr<move> get_transition_move() const;
    const std::vector<std::shared_ptr<piece>> &get_white_pieces() const;
    const std::vector<std::shared_ptr<piece>> &get_black_pieces() const;
    const std::vector<std::shared_ptr<piece>> get_all_pieces() const;
    std::shared_ptr<player> get_white_player() const;
    std::shared_ptr<player> get_black_player() const;
    std::shared_ptr<player> get_current_player() const;
    std::vector<std::shared_ptr<move>> get_all_legal_moves() const;
    std::shared_ptr<pawn> get_en_passant_pawn() const;
    /**
     * @brief The string representation of the board
     *
     * @return The string representation of the board
     */
    std::string stringify() const;

public: // Static functions
    /**
     * @brief Create a standard board
     *
     * @details Creates a standard board with all the pieces in their initial positions.
     *
     * @return A shared pointer to the created board
     */
    static std::shared_ptr<board> create_standard_board();

private: // Member functions
         /**
          * @brief Generate all the legal moves of a given set of pieces, and stream them into a vector.
          *
          * @param P The set of pieces
          * @return The set of legal moves
          */
    std::vector<std::shared_ptr<move>> calculate_legal_moves(const std::vector<std::shared_ptr<piece>> &P);
    /**
     * @brief Calculate the active pieces of a given alliance on the board.
     *
     * @param gb The game board
     * @param a The alliance
     * @return The active pieces of the alliance
     */
    static std::vector<std::shared_ptr<piece>> calculate_active_pieces(const std::array<std::shared_ptr<tile>, 64> &gb, alliance a);
    /**
     * @brief Create the array of all tiles using the set pieces on the board-builder.
     *
     * @param b The board builder
     * @return Array of tiles
     */
    static std::array<std::shared_ptr<tile>, 64> create_game_board(const board_builder &b);
    /**
     * @brief Initialize the game board using the board builder. This is private to make the board immutable.
     *
     * @param b The board builder
     */
    void initialize_game_board(const board_builder &b);

private: // Members
    friend class board_builder;

    std::shared_ptr<board> previous_board_ = nullptr;  ///< The previous board in the move tree
    std::shared_ptr<pawn> en_passant_pawn_ = nullptr;  ///< The en passant pawn
    std::shared_ptr<move> transition_move_ = nullptr;  ///< The move which led to this board
    std::array<std::shared_ptr<tile>, 64> game_board_; ///< The array of tiles representing the game board
    std::vector<std::shared_ptr<piece>> white_pieces_; ///< The vector of white pieces
    std::vector<std::shared_ptr<piece>> black_pieces_; ///< The vector of black pieces
    std::shared_ptr<white_player> white_player_;       ///< The white player
    std::shared_ptr<black_player> black_player_;       ///< The black player
    std::weak_ptr<player> current_player_;             ///< The current player
    int half_move_clock_ = 0;                          ///< The half move clock
    int full_move_number_ = 1;                         ///< The full move number
};

#endif // BOARD_HPP