#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <optional>
#include <memory>

template <typename T>
class Board {

public:
//    Board() { }
    Board(const std::size_t width, const std::size_t height) : width(width), height(height) {
        create();
    }
    virtual ~Board() {}

    Board(const std::shared_ptr<Board> board) : width(board->getWidth()), height(board->getHeight()) {
        create();
    }

    Board(const Board& board) : width(board.getWidth()), height(board.getHeight()) {
        create();
    }

    void create() {
        board.clear();
        board.reserve(getSize());
    }

    std::optional<std::shared_ptr<T>> getPieceAt(const std::size_t index) {
        if (index >= 0 && index < board.size())
            return board.at(index);
        return std::nullopt;
    }

    std::optional<std::shared_ptr<T>> getPieceAt(const std::size_t x, const std::size_t y) {
        if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight())
            return std::nullopt;
        return getPieceAt(y*getWidth()+x);
    }

    bool setPieceAt(const std::shared_ptr<T> piece, const std::size_t index) {
        if (index >= 0 && index < board.size()) {
            board.at(index) = piece;
            return true;
        } return false;
    }

    bool setPieceAt(const std::shared_ptr<T> piece, const std::size_t x, const std::size_t y) {
        return setPieceAt(piece, y*getWidth()+x);
    }

    std::size_t getWidth() const { return width; }
    std::size_t getHeight() const { return height; }
    std::size_t getSize() const { return width*height; }

protected:
    std::size_t width;
    std::size_t height;
    std::vector<std::shared_ptr<T>> board;
};

#endif