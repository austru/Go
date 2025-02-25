#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player();
    ~Player();
protected:
    std::string name;
    int rating;
};

#endif