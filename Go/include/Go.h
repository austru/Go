#ifndef GO_H
#define GO_H

#include "State.h"
#include "Player.h"
#include <vector>

class Go {

public:
    Go();
    ~Go();

    void placeStone(std::size_t);
    std::shared_ptr<GoBoard> getBoard();

protected:
    Player white;
    Player black;

    std::vector<std::size_t> players;
    int move;

    std::shared_ptr<GoBoard> board;
    State state;
};

#endif