#include "../include/number.h"

Number::Number(double value) : _value(value)
{
}

string Number::symbol()
{
    return convertValueToString();
}

string Number::value()
{
    return convertValueToString();
}

bool Number::match(Term *term)
{
    Variable *variable = term->getVariable();
    if (variable)
        variable->match(this);
    return value() == term->value();
}

string Number::convertValueToString() const
{
    std::stringstream ss;
    ss << _value;
    return ss.str();
}