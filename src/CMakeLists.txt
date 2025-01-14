add_subdirectory(engine)
add_subdirectory(gui)

set(MAIN_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ChessGame.cpp
    PARENT_SCOPE
)