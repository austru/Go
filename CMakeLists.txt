cmake_minimum_required(VERSION 3.10.0)
project(Go VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Go main.cpp 

    ${CMAKE_CURRENT_SOURCE_DIR}/src/GoBoard2D.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GoBoard.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GoUI.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Go.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IllegalMoveException.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Player.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Piece.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Stone.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Group.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/State.cc
    
)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_file(SDL2_INCLUDE_DIR REQUIRED NAME SDL.h HINTS SDL2)

target_include_directories(Go PRIVATE "${PROJECT_SOURCE_DIR}/include/")
target_link_libraries(Go PRIVATE SDL2::SDL2)

include(CTest)
enable_testing()

