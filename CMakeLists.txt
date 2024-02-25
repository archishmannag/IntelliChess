# CMake minimum version required
cmake_minimum_required(VERSION 3.12)

# Project name
project(Chess)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Set C++ standard
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)

# Add ncursesw library
find_library(CURSES_LIBRARY NAMES cursesw)
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARY})

# Add pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Add compile options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -std=c++17)

# Add install target
install(TARGETS ${PROJECT_NAME} DESTINATION bin)