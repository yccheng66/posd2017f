#include "../include/struct.h"

Struct::Struct(Atom functor, vector<Term *> args) : _functor(functor), _args(args)
{
}

string Struct::symbol()
{
    string ret = _functor.symbol() + "(";
    for (int i = 0; i < _args.size(); i++)
        ret += (((i > 0) ? ", " : "") + _args[i]->symbol());
    return ret + ")";
}

string Struct::value()
{
    string ret = _functor.symbol() + "(";
    for (int i = 0; i < _args.size(); i++)
        ret += (((i > 0) ? ", " : "") + _args[i]->value());
    return ret + ")";
}

bool Struct::match(Term *term)
{
    Variable *variable = term->getVariable();
    if (variable)
        return variable->match(this);
    Struct *structure = term->getStruct();
    if (!structure || !_functor.match(&(structure->_functor)) || _args.size() != structure->_args.size())
        return false;
    for (int i = 0; i < _args.size(); i++)
        if (!_args[i]->match(structure->_args[i]))
            return false;
    return true;
}

Struct *Struct::getStruct()
{
    return this;
}

Atom Struct::functor()
{
    return _functor;
}

Term *Struct::args(int index)
{
    if (index < _args.size())
        return _args[index];
    return nullptr;
}