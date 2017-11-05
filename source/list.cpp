#include "../include/list.h"
#include <iostream>

List::List(Term *head, Term *tail) : Struct(Atom("."), head, tail)
{
}

string List::symbol()
{
    string ret = "[";
    List *list;
    for (list = this; list && list->_args[_TAIL]; list = list->_args[_TAIL]->getList())
        ret += (((list != this) ? ", " : "") + list->_args[_HEAD]->symbol());
    return ret + "]";
}

string List::value()
{
    string ret = "[";
    List *list;
    for (list = this; list && list->_args[_TAIL]; list = list->_args[_TAIL]->getList())
        ret += (((list != this) ? ", " : "") + list->_args[_HEAD]->value());
    return ret + "]";
}

string List::structSymbol()
{
    string ret = _functor.symbol() + "(";
    for (int i = 0; i < _args.size(); i++)
        ret += ((i > 0) ? ", " : "") + ((_args[i]->getList()) ? _args[i]->getList()->structSymbol() : _args[i]->symbol());
    return ret + ")";
}

string List::structValue()
{
    string ret = _functor.symbol() + "(";
    for (int i = 0; i < _args.size(); i++)
        ret += ((i > 0) ? ", " : "") + ((_args[i]->getList()) ? _args[i]->getList()->structValue() : _args[i]->value());
    return ret + ")";
}

List *List::getList()
{
    return this;
}