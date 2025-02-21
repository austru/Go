#include "State.h"
#include <iostream>

State::State(const GoBoard& board) : board(board) {
    generateGroups();
    previous.push_back(this->board);
}
State::~State() {}
State::State(const State& state) : board(state.board) {
    for (auto group : state.groups)
        groups.insert(Group::create(group));
}


bool State::koRule() {
    return std::find_if(previous.begin(), previous.end(),
        [this](const GoBoard& board) { return this->board == board; } ) != previous.end();
}

std::set<std::shared_ptr<Group>> State::adjacentGroups(const std::shared_ptr<Stone> stone)
{
    std::set<std::shared_ptr<Group>> connected;
    std::copy_if(groups.begin(), groups.end(), std::inserter(connected, connected.end()),
        [&stone](std::shared_ptr<Group> group) { return group->hasStone(stone); } );
    return connected;
}

std::set<std::shared_ptr<Group>> State::adjacentGroups(const std::shared_ptr<Group> group)
{
    std::set<std::shared_ptr<Group>> connected;
    std::copy_if(groups.begin(), groups.end(), std::inserter(connected, connected.end()),
        [e = group->getEnemies()](std::shared_ptr<Group> group) { return group->hasStone(e); } );
    return connected;
}

void State::restore()
{
    if (!previous.empty()) {
        board = previous.back();
        generateGroups();
    }
}

std::vector<std::pair<int, int>> State::getScores()
{


    std::set<std::shared_ptr<Group>> empty;
    auto area = board.getEmpty();
    while (!area.empty()) {
        auto seed = (area.extract(area.begin())).value();
        auto group = Group::create(seed);
        search(area, group, seed);
        empty.insert(group);
    }

    std::vector<std::pair<int, int>> scores;

    for (auto liberty : empty)
        for (auto group : groups)
            if (liberty->getEnemies() == liberty->getStones(group->getId()))
                scores.push_back(std::make_pair(group->getId(), liberty->liberties()));

    std::cout<<"Number of groups: "<<groups.size()<<std::endl;
    std::cout<<"Number of liberty groups: "<<empty.size()<<std::endl;

    for (auto t : scores)
    {
        std::cout<<"Player id="<<t.first<<" += "<<t.second<<" points!"<<std::endl;
    }

    return scores;


}

void State::updateBoard(std::shared_ptr<GoBoard> board)
{
    previous.push_back(this->board);
    for (std::size_t i = 0; i < board->getSize(); i++)
        board->getPieceAt(i).value()->copy((this->board).getPieceAt(i).value());

    getScores();
}


void State::update(const std::shared_ptr<Stone> move) {
    if (!board.isEmptyAt(move->getPosition()))
        throw IllegalMoveException("Exception: Nonempty");

    auto stone = board.getPieceAt(move->getPosition()).value();
    stone->copy(move);

    auto group = Group::create(stone);
    group->addStones(board.adjacentStones(stone));

    for (auto g : adjacentGroups(stone))
        if (group->combine(g) || g->kill())
            groups.erase(g);

    if (group->isDead())
        throw IllegalMoveException("Suicide");
    if (koRule())
        throw IllegalMoveException("Ko Rule");

    groups.insert(group);
}


void State::search(std::set<std::shared_ptr<Stone>>& area, std::shared_ptr<Group> group, std::shared_ptr<Stone> stone) {
        for (const std::shared_ptr<Stone> adjacent : board.adjacentStones(stone))
            if (!group->hasStone(adjacent) && group->addStone(adjacent)->isFriendly(adjacent))
                    search(area, group, area.extract(adjacent).value());
}

void State::generateGroups() {
    groups.clear();
    auto area = board.getNonEmpty();
    while (!area.empty()) {
        auto seed = (area.extract(area.begin())).value();
        auto group = Group::create(seed);
        search(area, group, seed);
        if (group->isDead())
            throw IllegalMoveException("Illegal Position: Dead group");
        groups.insert(group);
    }
}