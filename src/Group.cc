#include "Group.h"
#include <iostream>

Group::Group(const int id) : id(id) {}

Group::Group(std::shared_ptr<Stone> stone) {
    this->id = stone->getId();
    addStone(stone);
}

Group::Group(const std::shared_ptr<Group> group) {
    this->id = group->getId();
    for (auto stone : group->stones)
        this->addStone(Stone::create(*stone));
}

Group *Group::addStone(std::shared_ptr<Stone> stone)
{
    stones.insert(stone);
    return this;
}

Group* Group::addStones(std::set<std::shared_ptr<Stone>> stones) {
    for (std::shared_ptr<Stone> stone : stones)
        addStone(stone);
    return this;
}

Group* Group::removeStone(std::shared_ptr<Stone> stone) {
    stones.erase(stone);
    return this;
}

bool Group::hasStone(const std::shared_ptr<Stone> stone) {
    return std::find(stones.begin(), stones.end(), stone) != stones.end();
}

bool Group::hasStone(const std::set<std::shared_ptr<Stone>> stones) {
    for (auto stone : stones)
        if (hasStone(stone))
            return true;
    return false;
}

bool Group::hasStone(const std::shared_ptr<Group> group) {
    for (auto stone : group->stones)
            if (hasStone(stone))
                return true;
    return false;
}

void Group::printStones() const
{
    std::cout<<"---------------------"<<std::endl;
    for (const auto stone : stones) {

    std::cout<<"liberties="<<liberties()<<", address = "<<stone.get()<<"id = "<<stone->getId()<<", position = "<<stone->getPosition()<<", type = "<<static_cast<int>(stone->getType())<<std::endl;
    
    }
    std::cout<<"---------------------"<<std::endl;
}

std::set<std::shared_ptr<Stone>> Group::getStones() const
{
    return stones;
}

std::set<std::shared_ptr<Stone>> Group::getStones(const int id) const
{
    std::set<std::shared_ptr<Stone>> matching;
    std::copy_if(stones.begin(), stones.end(), std::inserter(matching, matching.begin()),
        [&id](const std::shared_ptr<Stone> stone){
            return stone->getId() == id;
        });
    return matching;
}

std::set<std::shared_ptr<Stone>> Group::getFriendly() const
{
    std::set<std::shared_ptr<Stone>> friendly;
    std::copy_if(stones.begin(), stones.end(), std::inserter(friendly, friendly.begin()),
        [this](const std::shared_ptr<Stone> stone){
            return isFriendly(stone);
        });
    return friendly;
}

std::set<std::shared_ptr<Stone>> Group::getLiberties() const
{
    std::set<std::shared_ptr<Stone>> liberties;
    std::copy_if(stones.begin(), stones.end(), std::inserter(liberties, liberties.begin()),
        [this](const std::shared_ptr<Stone> stone){
            return stone->isEmpty();
        });
    return liberties;
}

std::set<std::shared_ptr<Stone>> Group::getEnemies() const
{
    std::set<std::shared_ptr<Stone>> enemies;
    std::copy_if(stones.begin(), stones.end(), std::inserter(enemies, enemies.begin()),
        [this](const std::shared_ptr<Stone> stone){
            return !stone->isEmpty() && !isFriendly(stone);
        });
    return enemies;
}

std::size_t Group::liberties() const
{
    return std::count_if(stones.begin(), stones.end(),
        [](const std::shared_ptr<Stone> stone) { return stone->isEmpty(); } );
}

bool Group::isDead() const {
    return liberties() == static_cast<std::size_t>(0);
}

bool Group::kill()
{
    if (!isDead())
        return false;
    for (auto stone : stones)
        if (isFriendly(stone))
            stone->setEmpty();
    return true;
}



bool Group::isFriendly(const std::shared_ptr<Stone> stone) const {
    return this->getId() == stone->getId();
}

bool Group::isFriendly(const std::shared_ptr<Group> group) const {
    return this->getId() == group->getId();
}


bool Group::combine(const std::shared_ptr<Group> group) {
    if (!isFriendly(group))
        return false;
    addStones(group->getStones());
    return true;
}


std::shared_ptr<Group> Group::getptr()
{
    return shared_from_this();
}

int Group::getId() const {
    return id;
}


