#include "../include/number.h"
#include <iostream>

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
        return variable->match(this);
    return value() == term->value();
}

// set the double precision to 12  //
string Number::convertValueToString() const
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(12) << _value;
    string ret = ss.str();

    int i = ret.find_last_not_of("0");
    if (i != string::npos)
        ret = ret.substr(0, i + ((ret[i] == '.') ? 0 : 1));
    return ret;
}