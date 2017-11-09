#include "../include/atom.h"

Atom::Atom(string symbol) : _symbol(symbol)
{
}

string Atom::symbol()
{
    return _symbol;
}

string Atom::value()
{
    return _symbol;
}

bool Atom::match(Term *term)
{
    Variable *variable = term->getVariable();
    if (variable)
        return variable->match(this);
    return value() == term->value();
}