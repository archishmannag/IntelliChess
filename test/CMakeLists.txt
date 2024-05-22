cmake_minimum_required(VERSION 3.20)

# Name of the test executable
set(EXECUTABLE_NAMES
	"BoardTest"
	"PieceTest"
	"PlayerTest"
)

set(SFML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/SFML-Linux/include)


foreach(EXECUTABLE_NAME ${EXECUTABLE_NAMES})

	add_executable(${EXECUTABLE_NAME} ${EXECUTABLE_NAME}.cpp)

	target_include_directories(${EXECUTABLE_NAME}
	PUBLIC "${PROJECT_SOURCE_DIR}/include"
	# PUBLIC ${SFML_INCLUDE_DIR}
	)

	target_link_libraries(${EXECUTABLE_NAME} PUBLIC
	gtest_main
	${PROJECT_NAME}_lib
	)

	if(UNIX AND NOT APPLE)
	add_compile_definitions(UNIX)
	endif(UNIX AND NOT APPLE)

	add_test(
		NAME ${EXECUTABLE_NAME}
		COMMAND ${EXECUTABLE_NAME}
	)

endforeach(EXECUTABLE_NAME ${EXECUTABLE_NAMES})