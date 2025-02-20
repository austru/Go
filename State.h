#include "GoBoard.h"
#include "IllegalMoveException.h"

class State {
public:
    State(const GoBoard&);
    ~State();
    State(const State&);

    auto operator<=>(const State& other) const
    {
        return previous.size() <=> other.previous.size();
    }
    bool operator==(const State& other) const
    {
        return board == other.board;
    }

    void generateGroups();
    void update(const std::shared_ptr<Stone>);
    void search(std::set<std::shared_ptr<Stone>>&, std::shared_ptr<Group>, std::shared_ptr<Stone>);
    bool koRule();

    std::set<std::shared_ptr<Group>> adjacentGroups(const std::shared_ptr<Stone>);
    std::set<std::shared_ptr<Group>> adjacentGroups(const std::shared_ptr<Group>);

    void restore();
    std::vector<std::pair<int, int>> getScores();

    void updateBoard(std::shared_ptr<GoBoard>);

protected:
    GoBoard board;
    std::set<std::shared_ptr<Group>> groups;
    std::vector<GoBoard> previous;
};