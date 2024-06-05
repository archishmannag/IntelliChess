# CMake minimum version required
cmake_minimum_required(VERSION 3.20)

# Project name
project(Chess VERSION 1.0.0 DESCRIPTION "Chess game" LANGUAGES CXX)

add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

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
if(UNIX)
	install(TARGETS ${PROJECT_NAME} DESTINATION bin)
endif(UNIX)

# Enable test and add its subdirectory
set(LIB_TEST ${PROJECT_NAME}_lib)
include(CTest)
set(BUILD_TESTING OFF)
if(BUILD_TESTING)
	enable_testing()

	# Update googletest submodule before building tests
	find_package(Git QUIET)
	if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
		option(GIT_SUBMODULE "Check submodules during build" ON)
		if (GIT_SUBMODULE)
			message(STATUS "Updating git submodules")
			execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			RESULT_VARIABLE GIT_SUBMOD_RESULT)
			if (NOT GIT_SUBMOD_RESULT EQUAL "0")
				message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
			endif(NOT GIT_SUBMOD_RESULT EQUAL "0")
		endif(GIT_SUBMODULE)
	endif(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")

	add_subdirectory(lib/googletest)
	add_library(${LIB_TEST} STATIC ${SOURCES})
	target_include_directories(${LIB_TEST} PRIVATE include PRIVATE ${SFML_DIR}/../../../include)
	target_link_libraries(${LIB_TEST} PRIVATE Threads::Threads PRIVATE sfml-graphics sfml-window sfml-audio)
	add_subdirectory(test)
endif(BUILD_TESTING)