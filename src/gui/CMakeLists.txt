# GUI CMAKELISTS

set(GUI_SOURCES PUBLIC
    Dialogs.cpp
    GameBoard.cpp
    GameHistory.cpp
    GameSetup.cpp
    GuiUtils.cpp
    Menu.cpp
    TakenPieces.cpp
)

add_library(GUI STATIC)

target_sources(GUI
    PRIVATE ${GUI_SOURCES}
    PUBLIC
    FILE_SET gui_headers TYPE HEADERS
    BASE_DIRS ${PROJECT_SOURCE_DIR}/include)

target_precompile_headers(GUI PUBLIC ${PROJECT_SOURCE_DIR}/include/PreCompiledHeaders.hpp)

target_link_libraries(GUI
    PUBLIC Engine
    PUBLIC sfml-graphics sfml-window sfml-system
)
