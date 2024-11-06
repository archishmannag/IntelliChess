# CMake minimum version required
cmake_minimum_required(VERSION 3.20)

# Project name
project(Chess VERSION 1.1.0 DESCRIPTION "Chess game" LANGUAGES CXX)

# Add project source directory and resource directory as a preprocessor definition for finding the assets
add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
add_definitions(-DPROJECT_RESOURCE_DIR="${CMAKE_SOURCE_DIR}/resources") # Change this to the path to resource directory when moving resources.

# Send build type to source code as a preprocessor definition
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-DDEBUG_BUILD)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	add_definitions(-DRELEASE_BUILD)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	add_definitions(-DRELWITHDEBINFO_BUILD)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
	add_definitions(-DMINSIZEREL_BUILD)
endif()

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

message(STATUS "Toolchain path: ${CMAKE_TOOLCHAIN_FILE}")

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Set C++ standard
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)

# Link SFML and pthread
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads PRIVATE sfml-graphics sfml-window sfml-system)

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE include PRIVATE ${SFML_DIR}/../../../include)

# Add precompiled header
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/PreCompiledHeaders.hpp)

# Add compile options with Compiler-specific flags
if(UNIX OR(WIN32 AND MINGW))
	# Use GCC or Clang specific flags
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -std=c++17)
elseif(WIN32 AND MSVC)
	# Use MSVC specific flags
	target_compile_options(${PROJECT_NAME} PRIVATE /W4 /EHsc /std:c++17)
endif(UNIX OR(WIN32 AND MINGW))

# Add icon for windows executable using resource file
if(WIN32)
	# Icon path
	set(ICON_PATH ${CMAKE_SOURCE_DIR}/resources/images/icon.ico)

	# Get resource file template and generated resource file
	set(RESOURCE_TEMPLATE ${CMAKE_SOURCE_DIR}/resources/icon.rc.in)
	set(GENERATED_RESOURCE ${CMAKE_BINARY_DIR}/icon.rc)
	configure_file(${RESOURCE_TEMPLATE} ${GENERATED_RESOURCE} @ONLY)

	# Add resource file to the executable
	target_sources(${PROJECT_NAME} PRIVATE ${GENERATED_RESOURCE})

	# Set resource compiler
	enable_language(RC)
	set(CMAKE_RC_COMPILER_INIT windres)
	set(CMAKE_RC_COMPILER windres)
endif(WIN32)

# Enable test and add its subdirectory
set(LIB_TEST ${PROJECT_NAME}_lib)
include(CTest)
set(BUILD_TESTING ON) # <--- Set to OFF to disable testing

if(BUILD_TESTING)
	enable_testing() # Add googletest library

	# Add googletest library
	find_package(GTest REQUIRED)

	# Add test target
	add_library(${LIB_TEST} STATIC ${SOURCES})

	# Set C++ standard
	set_target_properties(${LIB_TEST} PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED YES
		CXX_EXTENSIONS NO
	)

	# Add include directories
	target_include_directories(${LIB_TEST} PRIVATE include PRIVATE ${SFML_DIR}/../../../include)

	# Link SFML and pthread
	target_link_libraries(${LIB_TEST} PRIVATE Threads::Threads PRIVATE sfml-graphics sfml-window sfml-system)

	# Add precompiled header
	target_precompile_headers(${LIB_TEST} REUSE_FROM ${PROJECT_NAME})

	# Include the tests from its subdirectory
	add_subdirectory(test)
endif(BUILD_TESTING)