#include "Go.h"
#include <ranges>
#include <iostream>

Go::Go() : board(std::make_shared<GoBoard>(9, 9)), state(*board) {
    players.push_back(7);
    players.push_back(10);
    move = 0;
}


Go::~Go() {}


void Go::placeStone(std::size_t index)
{
    try {
        int test = (int)players.at(move%(int)players.size());
        auto stone = Stone::create(test, index);
        state.update(stone);
        state.updateBoard(board);
        move++;
    } catch (IllegalMoveException e) {
        printf("%s\n", e.what() );
        state.restore();
    }



}

std::shared_ptr<GoBoard> Go::getBoard()
{
    return board;
}

