/**
 * @file Move.hpp
 * @author your name (you@domain.com)
 * @brief Header file for all the moves, its derived classes and the move factory.
 * @version 1.0.0
 *
 */

#ifndef MOVE_HPP
#define MOVE_HPP

#include "PreCompiledHeaders.hpp"

// Forward declarations
class board;
class piece;
class rook;
class pawn;
class null_move;
enum class piece_type;

/**
 * @brief The different statuses of a move
 *
 */
enum class move_status
{
    done,
    illegal_move,
    leaves_player_in_check
};

/**
 * @brief The polymorphic move class
 *
 * @details This class is the base class for all types of moves in the game. It is a polymorphic class, and has derived classes for each type of move. This class is not to be instantiated but used as the base class for all types of moves.
 *
 */
class move
{
public: // Getters
    int get_destination_coordinate() const;
    int get_current_coordinate() const;
    std::shared_ptr<piece> get_moved_piece() const;
    /**
     * @brief Get the board on which the move is to be executed
     *
     * @return Pointer to the board
     */
    std::shared_ptr<board> get_board() const;

public: // Virtual functions
    virtual std::shared_ptr<piece> get_attacked_piece() const;
    virtual bool is_attack_move() const;
    virtual bool is_castling_move() const;
    /**
     * @brief Execute the move on the board, returning the new board
     *
     * @return Pointer to the new board
     */
    virtual std::shared_ptr<board> execute() const;
    /**
     * @brief The standard notation of a move
     *
     * @return String notation of the move
     */
    virtual std::string stringify() const;

public: // Operators
    /**
     * @brief Equality operator for moves; compares the various attributes of the move
     *
     * @param other The move to compare with
     * @return bool
     */
    virtual bool operator==(const move &other) const;

public: // functions
    /**
     * @brief Undo the move and return the previous board
     *
     * @return Poiner to the previous board
     */
    std::shared_ptr<board> undo() const;
    /**
     * @brief Static function to return the single null_move instance to not make a new instance every time
     *
     * @return Pointer to the null_move instance
     */
    static std::shared_ptr<move> get_null_move();

protected: // Constructors
    /**
     * @brief Construct a move with no moving piece (null_move)
     *
     * @param b The board on which the move is to be executed
     * @param dc The destination coordinate of the moving piece
     */
    move(std::shared_ptr<board> b, int dc);
    /**
     * @brief Construct a new move
     *
     * @param b The board on which the move is to be executed
     * @param mp The piece that is moved
     * @param dc The destination coordinate of the moving piece
     */
    move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc);

protected:
    /**
     * @brief If two moves have same piece and destination coordinate, differentiate their notations by adding the disambiguation file
     *
     * @return The file of the starting coordinate of the moving piece
     */
    std::string disambiguation_file() const;

protected:
    std::weak_ptr<board> board_;         ///< The board on which the move is to be executed
    std::shared_ptr<piece> moved_piece_; ///< The piece that is moved
    const int destination_coordinate_;   ///< The destination coordinate of the moving piece
    const bool is_first_move_;           ///< Whether the piece is moved for the first time (used for pawn jump and castling)

private: // Static members
    /**
     * @brief A null move as a static member so that we do not neet to instantiate null moves every time.
     *
     */
    static std::shared_ptr<null_move> null_move_;
};

/**
 * @brief Final class representing a major move (i.e. a non-attack move by a piece other than a pawn)
 *
 */
class major_move final : public move
{
public:
    /**
     * @brief Construct a new major move
     *
     * @param b The board on which the move is to be executed
     * @param mp The piece that is moved
     * @param dc The destination coordinate of the moving piece
     */
    major_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc);

    bool operator==(const move &other) const override;
    /**
     * @brief Return the standard notation of the move
     *
     * @return String notation of the move
     */
    std::string stringify() const override;
};

class attack_move : public move
{
public:
    bool operator==(const move &other) const override;

    /**
     * @brief Construct a new attack move
     *
     * @param b The board on which the move is to be executed
     * @param mp The piece that is moved
     * @param ap The piece that is attacked
     * @param dc The destination coordinate of the moving piece
     */
    attack_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, std::shared_ptr<piece> ap, int dc);
    bool is_attack_move() const override;
    std::shared_ptr<piece> get_attacked_piece() const override;

private:
    std::shared_ptr<piece> attacked_piece_; ///< The piece that is attacked
};

/**
 * @brief Final class representing a pawn promotion move
 *
 * @details This class represents a pawn promotion move. It holds the pawn to be promoted, the underlying move (a normal pawn move or a pawn attack move)
 * and the piece to which the pawn is to be promoted.
 *
 */
class pawn_promotion final : public move
{
public:
    /**
     * @brief Construct a new pawn promotion object
     *
     * @param im The underlying move
     * @param pp The piece to which the pawn is to be promoted
     */
    pawn_promotion(std::shared_ptr<move> im, std::shared_ptr<piece> pp);
    bool operator==(const move &other) const override;
    /**
     * @brief Execute the move on the board, returning the new board
     *
     * @return Pointer to the new board
     */
    std::shared_ptr<board> execute() const override;
    bool is_attack_move() const override;
    std::shared_ptr<piece> get_attacked_piece() const override;
    /**
     * @brief Get the piece to which the pawn is promoted
     *
     * @return Pointer to the promoted piece
     */
    std::shared_ptr<piece> get_promoted_piece() const;
    /**
     * @brief The standard notation of a move
     *
     * @return String notation of the move
     */
    std::string stringify() const override;

private:
    std::shared_ptr<move> input_move_;      ///< The underlying move
    std::shared_ptr<pawn> promoted_pawn_;   ///< The pawn to be promoted
    std::shared_ptr<piece> promoted_piece_; ///< The piece to which the pawn is to be promoted
};

/**
 * @brief Attack move by a major piece (i.e. a non-pawn piece)
 *
 */
class major_attack_move final : public attack_move
{
public:
    /**
     * @brief Construct a new major attack move
     *
     * @param b The board on which the move is to be executed
     * @param mp The piece that is moved
     * @param ap The piece that is attacked
     * @param dc The destination coordinate of the moving piece
     */
    major_attack_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, std::shared_ptr<piece> ap, int dc);
    bool operator==(const move &other) const override;
    /**
     * @brief The standard notation of a move
     *
     * @return String notation of the move
     */
    std::string stringify() const override;
};

/**
 * @brief Class representing a simple pawn move
 *
 */
class pawn_move final : public move
{
public:
    /**
     * @brief Construct a new pawn move
     *
     * @param b The board on which the move is to be executed
     * @param mp The piece that is moved
     * @param dc The destination coordinate of the moving piece
     */
    pawn_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc);
    bool operator==(const move &other) const override;
    /**
     * @brief The standard notation of a move
     *
     * @return String notation of the move
     */
    std::string stringify() const override;
};

/**
 * @brief Class representing a pawn attack move
 *
 */
class pawn_attack_move : public attack_move
{
public:
    /**
     * @brief Construct a new pawn attack move
     *
     * @param b The board on which the move is to be executed
     * @param mp The piece that is moved
     * @param ap The piece that is attacked
     * @param dc The destination coordinate of the moving piece
     */
    pawn_attack_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, std::shared_ptr<piece> ap, int dc);
    bool operator==(const move &other) const override;
    /**
     * @brief The standard notation of a move
     *
     * @return String notation of the move
     */
    std::string stringify() const override;
};

/**
 * @brief Class representing an en passant move
 *
 */
class pawn_en_passant_attack_move final : public pawn_attack_move
{
public:
    /**
     * @brief Construct a new pawn en passant attack move
     *
     * @param b The board on which the move is to be executed
     * @param mp The piece that is moved
     * @param ap The piece that is attacked
     * @param dc The destination coordinate of the moving piece
     */
    pawn_en_passant_attack_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, std::shared_ptr<piece> ap, int dc);
    /**
     * @brief Execute the move on the board, returning the new board
     *
     * @return Pointer to the new board
     */
    std::shared_ptr<board> execute() const override;
    bool operator==(const move &other) const override;
};

/**
 * @brief Class representing a pawn jump move
 *
 */
class pawn_jump final : public move
{
public:
    /**
     * @brief Construct a new pawn jump move
     *
     * @param b The board on which the move is to be executed
     * @param mp The piece that is moved
     * @param dc The destination coordinate of the moving piece
     */
    pawn_jump(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc);
    /**
     * @brief Execute the move on the board, returning the new board
     *
     * @return Pointer to the new board
     */
    std::shared_ptr<board> execute() const override;
    /**
     * @brief The standard notation of a move
     *
     * @return String notation of the move
     */
    std::string stringify() const override;
};

/**
 * @brief Class representing a castle move
 *
 * @details While this class does all the job, its two derived classes, king_side_castle_move and queen_side_castle_move, are used to generate the different notations
 * for these two types of moves (O-O and O-O-O respectively).
 */
class castle_move : public move
{
public:
    /**
     * @brief Construct a new castle move
     *
     * @param b The board on which the move is to be executed
     * @param mp The piece that is moved
     * @param dc The destination coordinate of the moving piece
     * @param cr The castling rook
     * @param crss The starting square of the castling rook
     * @param crd The destination square of the castling rook
     */
    castle_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc, std::shared_ptr<rook> cr, int crss, int crd);
    bool operator==(const move &other) const override;
    std::shared_ptr<rook> get_castling_rook() const;
    bool is_castling_move() const override;
    /**
     * @brief Execute the move on the board, returning the new board
     *
     * @return Pointer to the new board
     */
    std::shared_ptr<board> execute() const override;

protected:
    std::shared_ptr<rook> castling_rook_;  ///< The castling rook
    const int castling_rook_start_square_; ///< The starting square of the castling rook
    const int castling_rook_destination_;  ///< The destination square of the castling rook
};

/**
 * @brief Class representing king side castle move
 *
 */
class king_side_castle_move final : public castle_move
{
public:
    /**
     * @brief Construct a new king side castle move
     *
     * @param b The board on which the move is to be executed
     * @param mp The piece that is moved
     * @param dc The destination coordinate of the moving piece
     * @param cr The castling rook
     * @param crss The starting square of the castling rook
     * @param crd The destination square of the castling rook
     */
    king_side_castle_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc, std::shared_ptr<rook> cr, int crss, int crd);
    bool operator==(const move &other) const override;
    /**
     * @brief The standard notation of a move
     *
     * @return String notation of the move
     */
    std::string stringify() const override;
};

class queen_side_castle_move final : public castle_move
{
public:
    /**
     * @brief Construct a new queen side castle move
     *
     * @param b The board on which the move is to be executed
     * @param mp The piece that is moved
     * @param dc The destination coordinate of the moving piece
     * @param cr The castling rook
     * @param crss The starting square of the castling rook
     * @param crd The destination square of the castling rook
     */
    queen_side_castle_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc, std::shared_ptr<rook> cr, int crss, int crd);
    bool operator==(const move &other) const override;
    /**
     * @brief The standard notation of a move
     *
     * @return String notation of the move
     */
    std::string stringify() const override;
};

class null_move final : public move
{
public:
    /**
     * @brief Construct a new null move
     *
     */
    null_move();
    /**
     * @brief Execute the move on the board, returning the new board
     *
     * @return Pointer to the new board
     */
    std::shared_ptr<board> execute() const override;
    /**
     * @brief The standard notation of a move
     *
     * @return String notation of the move
     */
    std::string stringify() const override;
};

/**
 * @namespace move_factory
 * @brief Factory functions to create different types of moves
 *
 */
namespace move_factory
{
    /**
     * @brief Create a move
     *
     * @param b The board on which the move is to be executed
     * @param cc The current coordinate of the moving piece
     * @param dc The destination coordinate of the moving piece
     * @return Pointer to the created move
     */
    std::shared_ptr<move> create_move(std::shared_ptr<board> b, int cc, int dc);
    /**
     * @brief Create a pawn promotion move
     *
     * @param b The board on which the move is to be executed
     * @param cc The current coordinate of the moving piece
     * @param dc The destination coordinate of the moving piece
     * @param ppt The piece type to which the pawn is to be promoted
     * @return Pointer to the created move
     */
    std::shared_ptr<move> create_move(std::shared_ptr<board> b, int cc, int dc, piece_type ppt);
} // namespace move_factory

#endif // MOVE_HPP