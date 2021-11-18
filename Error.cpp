#include "Error.h"

void Error::Create(std::string _message, std::string _file)
{
    _isExists = true;
    this->_message = _message;
    this->_file = _file;
}

void Error::Print()
{
    std::cout << message();
    if (!file().empty())
    {
        std::cout << ": " << file();
    }
    std::cout << std::endl;
}

bool Error::isExists()
{
    return _isExists;
}

std::string Error::message()
{
    return _message;
}

std::string Error::file()
{
    return _file;
}