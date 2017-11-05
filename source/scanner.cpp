#include "../include/scanner.h"
#include <iostream>

Scanner::Scanner(string in) : _prolog(Prolog::getInstance()), _buffer(in), _position(0)
{
    //std::cout << "hello" << std::endl;
}

pair<string, int> Scanner::nextToken()
{
    if (skipLeadingWhiteSpace() >= _buffer.length())
        return pair<string, int>("", _prolog->EOS);
    else if (isdigit(currentChar()))
        return pair<string, int>(extractNumber(), _prolog->NUMBER);
    else if (islower(currentChar()))
        return pair<string, int>(extractAtom(), _prolog->ATOM);
    else if (_prolog->isSpecialChar(currentChar()))
        return pair<string, int>(extractAtomSC(), _prolog->ATOMSC);
    else if (isupper(currentChar()) || currentChar() == '_')
        return pair<string, int>(extractVariable(), _prolog->VARIABLE);
    else
    {
        char c = extractChar();
        return pair<string, int>(string(1, c), c);
    }
}

int Scanner::skipLeadingWhiteSpace()
{
    for (; _position < _buffer.length() && _buffer[_position] == ' ' || _buffer[_position] == '\t'; _position++)
        ;
    return _position;
}

string Scanner::extractNumber()
{
    int begin = _position;
    bool hasDot = false;
    for (; isdigit(_buffer[_position]) || (!hasDot && (hasDot = _buffer[_position] == '.')); _position++)
        ;
    return _buffer.substr(begin, _position - begin);
}

string Scanner::extractAtom()
{
    int begin = _position;
    for (; isalnum(_buffer[_position]); _position++)
        ;
    return _buffer.substr(begin, _position - begin);
}

string Scanner::extractAtomSC()
{
    int begin = _position;
    for (; _prolog->isSpecialChar(_buffer[_position]); _position++)
        ;
    return _buffer.substr(begin, _position - begin);
}

string Scanner::extractVariable()
{
    int begin = position();
    for (; isalnum(_buffer[_position]) || _buffer[_position] == '_'; _position++)
        ;
    return _buffer.substr(begin, _position - begin);
}

char Scanner::extractChar()
{
    return _buffer[_position++];
}

char Scanner::currentChar()
{
    return _buffer[_position];
}

int Scanner::position()
{
    return _position;
}