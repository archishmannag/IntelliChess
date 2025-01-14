# CMake minimum version required
cmake_minimum_required(VERSION 3.23)

# Project name
project(Chess VERSION 1.1.0 DESCRIPTION "Chess game" LANGUAGES CXX)

# Add project source directory and resource directory as a preprocessor definition for finding the assets
add_compile_definitions(PROJECT_RESOURCE_DIR="${CMAKE_SOURCE_DIR}/resources") # Change this to the path to resource directory when moving resources.

# Send build type to source code as a preprocessor definition
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_BUILD)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DRELEASE_BUILD)
endif()

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add compile options with Compiler-specific flags
if(UNIX OR(WIN32 AND MINGW))
    # Use GCC or Clang specific flags
    set(OPTIONS PRIVATE -Wall -Wextra -Wpedantic -std=c++17)
elseif(WIN32 AND MSVC)
    # Use MSVC specific flags
    set(OPTIONS PRIVATE /W4 /EHsc /std:c++17)
endif(UNIX OR(WIN32 AND MINGW))

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add pthread library
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(src)

# Add executable target
add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE Engine
    PRIVATE GUI
)

target_compile_options(${PROJECT_NAME} ${OPTIONS})

# Add icon for windows executable using resource file
if(WIN32)
    # Icon path
    set(ICON_PATH ${CMAKE_SOURCE_DIR}/resources/images/icon.ico)

    # Get resource file template and generated resource file
    set(RESOURCE_TEMPLATE ${CMAKE_SOURCE_DIR}/resources/icon.rc.in)
    set(GENERATED_RESOURCE ${CMAKE_BINARY_DIR}/icon.rc)
    configure_file(${RESOURCE_TEMPLATE} ${GENERATED_RESOURCE} @ONLY)

    if(MINGW)
        # Use windres for MinGW
        enable_language(RC)
        set(CMAKE_RC_COMPILER_INIT windres)
        set(CMAKE_RC_COMPILER windres)

        # Add resource file to the executable
        target_sources(${PROJECT_NAME} PRIVATE ${GENERATED_RESOURCE})
    elseif(MSVC)
        # Use rc.exe for MSVC
        set(CMAKE_RC_COMPILER rc)
        add_custom_command(
            OUTPUT ${CMAKE_BINARY_DIR}/icon.rc.res
            COMMAND ${CMAKE_RC_COMPILER} /fo ${CMAKE_BINARY_DIR}/icon.rc.res ${GENERATED_RESOURCE}
            DEPENDS ${GENERATED_RESOURCE}
        )

        # # Add resource file to the executable
        target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/icon.rc.res)
    endif()
endif(WIN32)

# Enable test and add its subdirectory
option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    set(LIB_TEST ${PROJECT_NAME}_lib)
    include(CTest)

    enable_testing() # Add googletest library

    # Add googletest library
    find_package(GTest REQUIRED)

    # Include the tests from its subdirectory
    add_subdirectory(test)
endif(BUILD_TESTS)
