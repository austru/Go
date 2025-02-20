#include <stdexcept>
#include <string>

class IllegalMoveException : public std::exception {

public:
    IllegalMoveException(const std::string& message);
    const char* what() const noexcept override;
private:
    std::string message;
};