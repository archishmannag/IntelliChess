# CMake minimum version required
cmake_minimum_required(VERSION 3.12)

# Project name
project(Chess)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Set SFML directory
set(SFML_DIR ${CMAKE_SOURCE_DIR}/lib/SFML-Linux/lib/cmake/SFML)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window audio REQUIRED)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Set C++ standard
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)

# Add pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Link SFML and pthread
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads PRIVATE sfml-graphics sfml-window sfml-audio)

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE include PRIVATE ${SFML_DIR}/../../../include)

# Add compile options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -std=c++17)

# Add install target
install(TARGETS ${PROJECT_NAME} DESTINATION bin)