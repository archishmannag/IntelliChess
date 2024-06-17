# CMake minimum version required
cmake_minimum_required(VERSION 3.20)

# Project name
project(Chess VERSION 1.0.0 DESCRIPTION "Chess game" LANGUAGES CXX)

# Add project source directory as a preprocessor definition for finding the assets
add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

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

# Set SFML directory
if(UNIX)
	set(SFML_DIR ${CMAKE_SOURCE_DIR}/lib/SFML-Linux/lib/cmake/SFML)
elseif(WIN32 AND MINGW)
	set(SFML_DIR ${CMAKE_SOURCE_DIR}/lib/SFML-Windows-MinGW/lib/cmake/SFML)
elseif(WIN32 AND MSVC)
	set(SFML_DIR ${CMAKE_SOURCE_DIR}/lib/SFML-Windows-MSVC/lib/cmake/SFML)
endif(UNIX)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

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

# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -std=c++17)
if(WIN32)
	# Find SFML DLLs
	file(GLOB SFML_DLLS ${SFML_DIR}/../../../bin/*.dll)

	# Copy the DLLs to the output directory
	file(COPY ${SFML_DLLS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif(WIN32)

# Add install target
if(UNIX)
	install(TARGETS ${PROJECT_NAME} DESTINATION bin)
endif(UNIX)

# Enable test and add its subdirectory
set(LIB_TEST ${PROJECT_NAME}_lib)
include(CTest)
set(BUILD_TESTING ON)

if(BUILD_TESTING)
	enable_testing()

	# Update googletest submodule before building tests
	find_package(Git QUIET)

	if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
		option(GIT_SUBMODULE "Check submodules during build" ON)

		if(GIT_SUBMODULE)
			message(STATUS "Updating git submodules")
			execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
				WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
				RESULT_VARIABLE GIT_SUBMOD_RESULT)

			if(NOT GIT_SUBMOD_RESULT EQUAL "0")
				message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
			endif(NOT GIT_SUBMOD_RESULT EQUAL "0")
		endif(GIT_SUBMODULE)
	endif(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")

	add_subdirectory(lib/googletest)
	add_library(${LIB_TEST} STATIC ${SOURCES})
	target_include_directories(${LIB_TEST} PRIVATE include PRIVATE ${SFML_DIR}/../../../include)
	target_link_libraries(${LIB_TEST} PRIVATE Threads::Threads PRIVATE sfml-graphics sfml-window sfml-system)
	target_precompile_headers(${LIB_TEST} REUSE_FROM ${PROJECT_NAME})
	add_subdirectory(test)
endif(BUILD_TESTING)