#include "../include/utility.h"

Utility *Utility::_instance = nullptr;

Utility *Utility::getInstance()
{
    if (!_instance)
        _instance = new Utility();
    return _instance;
}

bool Utility::isSpecialChar(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '<' || c == '>' || c == '.' || c == '&' || c == '\\' || c == '~' || c == '^' || c == '$' || c == '#' || c == '@' || c == '?' || c == ':';
}

Utility::Utility()
{
}
