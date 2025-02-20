#include "Stone.h"
#include <iostream>
/* Represents empty; not placed by player */
Stone::Stone(const std::size_t position) {
    setPosition(position);
    setType(StoneType::Empty);
}

Stone::Stone(const int id, const std::size_t position) {
    setId(id);
    setPosition(position);
    setType(StoneType::NonEmpty);
}

Stone::Stone(const std::shared_ptr<Stone> stone)
{
    copy(stone);
}

std::shared_ptr<Stone> Stone::getptr()
{
    return shared_from_this();
}

void Stone::copy(const std::shared_ptr<Stone> stone)
{
    this->setId(stone->getId());
    this->setPosition(stone->getPosition());
    this->setType(stone->getType());
}

void Stone::setId(const int id)
{
    this->id = id;
}

int Stone::getId() const {
    return this->id;
}

void Stone::setType(StoneType type) {
    this->type = type;
    if (this->isEmpty())
        this->setId(static_cast<int>(StoneType::Empty));
}

void Stone::setPosition(const std::size_t position)
{
    this->position = position;
}

std::size_t Stone::getPosition() const
{
    return this->position;
}

StoneType Stone::getType() const {
    return this->type;
}

void Stone::setEmpty()
{
    this->setType(StoneType::Empty);
}

bool Stone::isEmpty() const
{
    return this->getType() == StoneType::Empty;
}

