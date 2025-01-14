# Engine CMAKELIST

set(ENGINE_SOURCES

    # Board
    board/Board.cpp
    board/BoardUtils.cpp
    board/Move.cpp
    board/MoveTransition.cpp
    board/Tile.cpp

    # Pieces
    pieces/Bishop.cpp
    pieces/King.cpp
    pieces/Knight.cpp
    pieces/Pawn.cpp
    pieces/Piece.cpp
    pieces/Queen.cpp
    pieces/Rook.cpp

    # Player
    player/BlackPlayer.cpp
    player/Player.cpp
    player/WhitePlayer.cpp
    player/ai/AlphaBeta.cpp
    player/ai/MiniMax.cpp
    player/ai/PawnStructureAnalyzer.cpp
    player/ai/StandardBoardEvaluator.cpp

    # Utils
    utility/FenUtils.cpp
    utility/PgnUtils.cpp

    Alliance.cpp
)

add_library(Engine STATIC)

target_sources(Engine
    PRIVATE ${ENGINE_SOURCES}
    PUBLIC
    FILE_SET engine_headers TYPE HEADERS
    BASE_DIRS ${PROJECT_SOURCE_DIR}/include)

target_precompile_headers(Engine PUBLIC ${PROJECT_SOURCE_DIR}/include/PreCompiledHeaders.hpp)

set_target_properties(Engine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/lib
)
