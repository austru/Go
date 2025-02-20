#include "GoBoard.h"
#include <iostream>

//GoBoard::GoBoard() : Board<Stone>() {}
GoBoard::GoBoard(const std::size_t width, const std::size_t height) : Board<Stone>(width, height) {
    for (std::size_t i = 0; i < getSize(); ++i)
        this->board.push_back(Stone::create(i));
}
GoBoard::~GoBoard() {}

GoBoard& GoBoard::operator=(const GoBoard& other)
{
    if (this != &other) {
        this->width = other.width;
        this->height = other.height;
        create();
        for (auto stone : other.board)
            this->board.push_back(Stone::create(stone));
    }
    return *this;
}

bool GoBoard::operator==(const GoBoard &other) const
{
    return std::equal(board.begin(), board.end(), other.board.begin(),
        [](const std::shared_ptr<Stone> a, const std::shared_ptr<Stone> b) {
            return *a == *b;
        } );
}


GoBoard::GoBoard(const GoBoard& board) : Board<Stone>(board)
{
    for (auto stone : board.board)
        this->board.push_back(Stone::create(stone));
}

std::set<std::shared_ptr<Stone>> GoBoard::adjacentStones(const std::shared_ptr<Stone> stone)
{
    std::set<std::shared_ptr<Stone>> adjacent;

    std::size_t x = stone->getPosition() % getWidth();
    std::size_t y = stone->getPosition() / getHeight();

    if (auto left = getPieceAt(x - 1, y); left.has_value())
        adjacent.insert(left.value());
    if (auto right = getPieceAt(x + 1, y); right.has_value())
        adjacent.insert(right.value());
    if (auto up = getPieceAt(x, y + 1); up.has_value())
        adjacent.insert(up.value());
    if (auto down = getPieceAt(x, y - 1); down.has_value())
        adjacent.insert(down.value());

    return adjacent;    
}

std::set<std::shared_ptr<Stone>> GoBoard::getNonEmpty()
{
    std::set<std::shared_ptr<Stone>> nonEmpty;
    std::copy_if(board.begin(), board.end(), std::inserter(nonEmpty, nonEmpty.end()),
        [](const std::shared_ptr<Stone> stone) { return !stone->isEmpty(); }
    );
    return nonEmpty;
}

std::set<std::shared_ptr<Stone>> GoBoard::getEmpty()
{
    std::set<std::shared_ptr<Stone>> empty;
    std::copy_if(board.begin(), board.end(), std::inserter(empty, empty.end()),
        [](const std::shared_ptr<Stone> stone) { return stone->isEmpty(); }
    );
    return empty;
}

bool GoBoard::isEmptyAt(const std::size_t index)
{
    if (auto location = getPieceAt(index); location.has_value())
        return location.value()->getType() == StoneType::Empty;
    return false;
}


void GoBoard::updateState()
{

}

void GoBoard::setState()
{

}


void GoBoard::printBoard() const
{
    std::cout<<"------- Board -------"<<std::endl;
    std::cout<<"width = "<<getWidth()<<std::endl;
    std::cout<<"height = "<<getHeight()<<std::endl;
    std::cout<<"size = "<<getSize()<<std::endl;
    std::cout<<"actual board.size() = "<<board.size()<<std::endl;
    for (int i = 0; i < board.size(); i++) {
            std::cout<<board.at(i)->getId();
            if ((i+1) % getWidth() == 0)
                std::cout<<std::endl;
    }
    std::cout<<"---------------------"<<std::endl;
    
}