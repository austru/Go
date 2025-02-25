cmake_minimum_required(VERSION 3.10.0)
project(Go VERSION 0.1.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions(-std=c++20)

include_directories(include)

add_executable(Go main.cpp) 

target_sources(Go PRIVATE

    src/GoBoard2D.cc
    src/GoBoard.cc
    src/GoUI.cc
    src/Go.cc
    src/IllegalMoveException.cc
    src/Player.cc
    src/Piece.cc
    src/Stone.cc
    src/Group.cc
    src/State.cc
    
)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED)

target_link_libraries(Go PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)


