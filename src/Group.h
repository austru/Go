#pragma once

#include <set>
#include <memory>
#include <algorithm>
#include <optional>
#include "Stone.h"

class Group : public std::enable_shared_from_this<Group> {

private:
    Group(const int);
    Group(std::shared_ptr<Stone>);
    Group(const std::shared_ptr<Group>);

public:

    template<typename... T>
    static std::shared_ptr<Group> create(T&&... t) {

        struct Private : public Group {
            Private(T&&... arg) : Group(std::forward<T>(arg)...) {}
        };

        return std::make_shared<Private>(std::forward<T>(t)...);
    }

    std::shared_ptr<Group> getptr();

    auto operator<=>(const Group& stone) const = default;

    //Group operator+(const Group&) const;

    Group* addStone(std::shared_ptr<Stone>);
    Group* addStones(std::set<std::shared_ptr<Stone>>);
    Group* removeStone(std::shared_ptr<Stone>);
    bool combine(const std::shared_ptr<Group>);
    bool hasStone(const std::shared_ptr<Stone>);
    bool hasStone(const std::set<std::shared_ptr<Stone>>);
    bool hasStone(const std::shared_ptr<Group>);

    void printStones() const;

    std::set<std::shared_ptr<Stone>> getStones() const;
    std::set<std::shared_ptr<Stone>> getStones(const int id) const;
    std::set<std::shared_ptr<Stone>> getFriendly() const;
    std::set<std::shared_ptr<Stone>> getLiberties() const;
    std::set<std::shared_ptr<Stone>> getEnemies() const;
    std::size_t liberties() const;
    bool isDead() const;
    bool kill();
    bool isFriendly(const std::shared_ptr<Stone>) const;
    bool isFriendly(const std::shared_ptr<Group>) const;
    int getId() const;
protected:
    int id;
    std::set<std::shared_ptr<Stone>> stones;
};

