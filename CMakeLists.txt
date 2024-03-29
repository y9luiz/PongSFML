﻿# CMakeList.txt : CMake project for SFMLPong, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("SFMLPong")

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "<PATH>SFML-2.5.1/lib/cmake/SFML" CACHE PATH "Path to lib SFML version 2.5.1")

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)


# Add source to this project's executable.
add_executable (SFMLPong "SFMLPong.cpp" "SFMLPong.h" "defs.h" "paddle.h" "paddle.cpp" "collider.h" "ball.h" "ball.cpp" "circle.h" "screen.h" "game_screen.h" "game_screen.cpp" "button.h" "button.cpp")
target_link_libraries(SFMLPong PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

include(cmake/file_macros.cmake)
COPY_FILES_FROM_FOLDER(Assets)
IF (WIN32)
	COPY_FILES_FROM_FOLDER(libs/x64)
	MOVE_DLLS_FROM_FOLDER(${CMAKE_BINARY_DIR}/libs/x64 ${CMAKE_BINARY_DIR})
ENDIF()
# TODO: Add tests and install targets if needed.
