#pragma once

#include "Board.h"
#include "Group.h"
#include <algorithm>
#include <set>

class GoBoard : public Board<Stone> {

public:
//   GoBoard();
    GoBoard(const std::size_t, const std::size_t);
    virtual ~GoBoard();

    GoBoard& operator=(const GoBoard&);
    auto operator<=>(const GoBoard& other) const
    {
        return board <=> other.board;
    }
    bool operator==(const GoBoard&) const;

    GoBoard(const GoBoard&);

    std::set<std::shared_ptr<Stone>> adjacentStones(const std::shared_ptr<Stone>);
    std::set<std::shared_ptr<Stone>> getNonEmpty();
    std::set<std::shared_ptr<Stone>> getEmpty();

    void printBoard() const;

    bool isEmptyAt(const std::size_t);
    void setState();
    void updateState();
    void clearState();
};