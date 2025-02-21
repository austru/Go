#ifndef STONE_H
#define STONE_H

#include <compare>
#include <memory>

enum class StoneType {
        Empty,
        NonEmpty
};

class Stone : public std::enable_shared_from_this<Stone> {
    
private:

    Stone(const std::size_t);
    Stone(const int, const std::size_t);
    Stone(const std::shared_ptr<Stone>);


public:

    template<typename... T>
    static std::shared_ptr<Stone> create(T&&... t) {

        struct Private : public Stone {
            Private(T&&... arg) : Stone(std::forward<T>(arg)...) {}
        };

        return std::make_shared<Private>(std::forward<T>(t)...);
    }

    auto operator<=>(const Stone& other) const {
       return std::tie(id, position, type) <=> std::tie(other.id, other.position, other.type); 
    }
    bool operator==(const Stone& other) const {
       return std::tie(id, position, type) == std::tie(other.id, other.position, other.type); 
    }

    std::shared_ptr<Stone> getptr();

    void copy(const std::shared_ptr<Stone>);
    void setId(const int);
    int getId() const;
    void setType(StoneType);
    StoneType getType() const;

    std::size_t getPosition() const;

    void setEmpty();
    bool isEmpty() const;
protected:
    void setPosition(const std::size_t);

    int id;
    std::size_t position;
    StoneType type;
};

#endif