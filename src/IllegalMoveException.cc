#include "IllegalMoveException.h"

IllegalMoveException::IllegalMoveException(const std::string &message)
{
    this->message = message;
}

const char *IllegalMoveException::what() const noexcept
{
    return this->message.c_str();
}
