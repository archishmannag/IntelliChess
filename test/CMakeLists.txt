# Define the minimum version of CMake required
cmake_minimum_required(VERSION 3.20)

# Name of the test executable
set(EXECUTABLE_NAMES
	"BoardTest"
	"PieceTest"
	"PlayerTest"
)

foreach(EXECUTABLE_NAME ${EXECUTABLE_NAMES})
	# Add the executable
	add_executable(${EXECUTABLE_NAME} ${EXECUTABLE_NAME}.cpp)

	# Set the C++ standard
	set_target_properties(${PROJECT_NAME} PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED YES
		CXX_EXTENSIONS NO
	)

	# Include the headers
	target_include_directories(${EXECUTABLE_NAME}
		PUBLIC "${PROJECT_SOURCE_DIR}/include"
	)

	# Link the executable to the source library and googletest
	target_link_libraries(${EXECUTABLE_NAME} PUBLIC
		GTest::gtest_main
		${PROJECT_NAME}_lib
	)

	# Add the precompiled headers
	target_precompile_headers(${EXECUTABLE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/PreCompiledHeaders.hpp)

	if(UNIX AND NOT APPLE)
		add_compile_definitions(UNIX)
	endif(UNIX AND NOT APPLE)

	# Add the test
	add_test(
		NAME ${EXECUTABLE_NAME}
		COMMAND ${EXECUTABLE_NAME}
	)
endforeach(EXECUTABLE_NAME ${EXECUTABLE_NAMES})