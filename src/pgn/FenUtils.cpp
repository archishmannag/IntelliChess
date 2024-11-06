/**
 * @file FenUtils.cpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Implementation of the FEN utilities
 * @version 1.1.0
 *
 */

#include "pgn/FenUtils.hpp"
#include "engine/Alliance.hpp"
#include "engine/board/Board.hpp"
#include "engine/board/BoardUtils.hpp"
#include "engine/board/Tile.hpp"
#include "engine/pieces/Bishop.hpp"
#include "engine/pieces/King.hpp"
#include "engine/pieces/Knight.hpp"
#include "engine/pieces/Pawn.hpp"
#include "engine/pieces/Piece.hpp"
#include "engine/pieces/Queen.hpp"
#include "engine/pieces/Rook.hpp"
#include "engine/player/Player.hpp"

/**
 * @brief Helper functions for the Board to FEN conversion
 *
 */
namespace
{
    std::string calculate_board_text(const board &b)
    {
        std::string board_pieces_string = "";
        for (int i = 0; i < 64; i++)
        {
            board_pieces_string += b.get_tile(i)->stringify();
            if (i % 8 == 7)
                board_pieces_string += "/";
        }
        board_pieces_string.erase(board_pieces_string.end() - 1); // Remove the last '/'

        board_pieces_string = std::regex_replace(board_pieces_string, std::regex("--------"), "8");
        board_pieces_string = std::regex_replace(board_pieces_string, std::regex("-------"), "7");
        board_pieces_string = std::regex_replace(board_pieces_string, std::regex("------"), "6");
        board_pieces_string = std::regex_replace(board_pieces_string, std::regex("-----"), "5");
        board_pieces_string = std::regex_replace(board_pieces_string, std::regex("----"), "4");
        board_pieces_string = std::regex_replace(board_pieces_string, std::regex("---"), "3");
        board_pieces_string = std::regex_replace(board_pieces_string, std::regex("--"), "2");
        board_pieces_string = std::regex_replace(board_pieces_string, std::regex("-"), "1");

        return board_pieces_string;
    }

    std::string calculate_current_player_text(const board &b)
    {
        std::string current_player_text = alliance_utils::stringify(b.get_current_player()->get_player_alliance()).substr(0, 1);
        for (char &c : current_player_text)
            c = std::tolower(c);
        return current_player_text;
    }

    std::string calculate_castling_rights_text(const board &b)
    {
        std::string res = "";
        if (b.get_white_player()->is_king_side_castle_capable())
            res += "K";
        if (b.get_white_player()->is_queen_side_castle_capable())
            res += "Q";
        if (b.get_black_player()->is_king_side_castle_capable())
            res += "k";
        if (b.get_black_player()->is_queen_side_castle_capable())
            res += "q";
        if (res == "")
            res = "-";
        return res;
    }

    std::string calculate_en_passant_text(const board &b)
    {
        const std::shared_ptr<pawn> &en_passant_pawn = b.get_en_passant_pawn();
        if (en_passant_pawn == nullptr)
            return "-";
        else
            return board_utils::get_position_at_coordinate(en_passant_pawn->get_piece_position() + (8 * alliance_utils::get_opposite_direction(en_passant_pawn->get_piece_alliance())));
    }

    std::string calculate_halfmove_clock_text(const board &b)
    {
        return std::to_string(b.get_half_move_clock());
    }

    std::string calculate_fullmove_number_text(const board &b)
    {
        return std::to_string(b.get_full_move_number());
    }
} // namespace

/**
 * @brief Helper functions for the FEN to board conversion
 *
 */
namespace
{
    /**
     * @brief Implementation of trim, as it is not available in C++
     *
     * @param s
     * @return std::string
     */
    static inline std::string trim(std::string s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                        { return !std::isspace(ch); }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                             { return !std::isspace(ch); })
                    .base(),
                s.end());
        return s;
    }

    /**
     * @brief Implementation of split (with single char delimeter), as it is not available in C++
     *
     * @param s
     * @param delim
     * @return std::vector<std::string>
     */
    static inline std::vector<std::string> split(std::string s, const char &delim)
    {
        std::vector<std::string> result;
        std::size_t start = 0,
                    pos = s.find(delim);
        while (pos != std::string::npos)
        {
            result.push_back(s.substr(start, pos - start));
            start = pos + 1;
            pos = s.find(delim, start);
        }
        result.push_back(s.substr(start));
        return result;
    }

    static inline bool white_king_side_castle_capable(const std::string &s)
    {
        return s.find('K') != std::string::npos;
    }

    static inline bool white_queen_side_castle_capable(const std::string &s)
    {
        return s.find('Q') != std::string::npos;
    }

    static inline bool black_king_side_castle_capable(const std::string &s)
    {
        return s.find('k') != std::string::npos;
    }

    static inline bool black_queen_side_castle_capable(const std::string &s)
    {
        return s.find('q') != std::string::npos;
    }

    static inline alliance move_maker(const std::string &s)
    {
        if (s == "w")
            return alliance::white;
        else if (s == "b")
            return alliance::black;
        else
            throw std::runtime_error("Invalid move maker string");
    }

    static inline std::shared_ptr<pawn> en_passant_pawn(const std::string &s, const board_builder &b)
    {
        if (s == "-")
            return nullptr;
        else
        {
            int en_passant_pawn_position = board_utils::get_coordinate_at_position(s[0] + std::to_string(std::stoi(s.substr(1, 1)) + alliance_utils::get_direction(b.get_next_move_maker())));
            return std::dynamic_pointer_cast<pawn>(b.get_board_config().at(en_passant_pawn_position));
        }
    }

    std::shared_ptr<board> parse_fen(const std::string &fen)
    {
        std::vector<std::string> fen_parts = split(trim(fen), ' ');
        if (fen_parts.size() != 6)
            throw std::runtime_error("Invalid FEN string");
        board_builder builder;
        bool white_king_castle_capable = white_king_side_castle_capable(fen_parts[2]),
             white_queen_castle_capable = white_queen_side_castle_capable(fen_parts[2]),
             black_king_castle_capable = black_king_side_castle_capable(fen_parts[2]),
             black_queen_castle_capable = black_queen_side_castle_capable(fen_parts[2]);
        std::string board_text = fen_parts[0];

        board_text = std::regex_replace(board_text, std::regex("8"), "--------");
        board_text = std::regex_replace(board_text, std::regex("7"), "-------");
        board_text = std::regex_replace(board_text, std::regex("6"), "------");
        board_text = std::regex_replace(board_text, std::regex("5"), "-----");
        board_text = std::regex_replace(board_text, std::regex("4"), "----");
        board_text = std::regex_replace(board_text, std::regex("3"), "---");
        board_text = std::regex_replace(board_text, std::regex("2"), "--");
        board_text = std::regex_replace(board_text, std::regex("1"), "-");
        board_text = std::regex_replace(board_text, std::regex("/"), "");

        int i = 0;
        while (i < (int)board_text.size())
        {
            switch (board_text[i])
            {
            case 'P':
                builder.set_piece(std::make_shared<pawn>(i, alliance::white));
                i++;
                break;
            case 'N':
                builder.set_piece(std::make_shared<knight>(i, alliance::white));
                i++;
                break;
            case 'B':
                builder.set_piece(std::make_shared<bishop>(i, alliance::white));
                i++;
                break;
            case 'R':
                builder.set_piece(std::make_shared<rook>(i, alliance::white));
                i++;
                break;
            case 'Q':
                builder.set_piece(std::make_shared<queen>(i, alliance::white));
                i++;
                break;
            case 'K':
                builder.set_piece(std::make_shared<king>(i, alliance::white, true, false, white_king_castle_capable, white_queen_castle_capable));
                i++;
                break;
            case 'p':
                builder.set_piece(std::make_shared<pawn>(i, alliance::black));
                i++;
                break;
            case 'n':
                builder.set_piece(std::make_shared<knight>(i, alliance::black));
                i++;
                break;
            case 'b':
                builder.set_piece(std::make_shared<bishop>(i, alliance::black));
                i++;
                break;
            case 'r':
                builder.set_piece(std::make_shared<rook>(i, alliance::black));
                i++;
                break;
            case 'q':
                builder.set_piece(std::make_shared<queen>(i, alliance::black));
                i++;
                break;
            case 'k':
                builder.set_piece(std::make_shared<king>(i, alliance::black, true, false, black_king_castle_capable, black_queen_castle_capable));
                i++;
                break;
            case '-':
                i++;
                break;
            default:
                throw std::runtime_error("Invalid piece character in FEN string");
            }
        }
        builder.set_move_maker(move_maker(fen_parts[1]));
        builder.set_en_passant_pawn(en_passant_pawn(fen_parts[3], builder));
        builder.set_half_move_clock(std::stoi(fen_parts[4]));
        builder.set_full_move_number(std::stoi(fen_parts[5]));
        return builder.build();
    }
} // namespace

std::shared_ptr<board> fen_utils::fen_to_board(const std::string &fen)
{
    return parse_fen(fen);
}

std::string fen_utils::board_to_fen(const board &b)
{
    return calculate_board_text(b) + " " + calculate_current_player_text(b) + " " + calculate_castling_rights_text(b) + " " + calculate_en_passant_text(b) + " " + calculate_halfmove_clock_text(b) + " " + calculate_fullmove_number_text(b);
}