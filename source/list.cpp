#include "../include/list.h"
#include <iostream>

List::List(vector<Term *> args) : Struct(Atom("."), args)
{
}

string List::symbol()
{
    string ret = "[";
    List *list = this;
    for (; list; list = list->_args[1]->getList())
        ret += (((list != this) ? ", " : "") + list->_args[0]->symbol());
    return ret + "]";
}

string List::value()
{
    string ret = "[";
    List *list = this;
    for (; list; list = list->_args[1]->getList())
        ret += (((list != this) ? ", " : "") + list->_args[0]->value());
    return ret + "]";
}

List *List::getList()
{
    return this;
}

/*List::List(vector<Term *> args, bool isConcat) : _args(args), _isConcat(isConcat)
{
}

string List::symbol()
{
    string ret = "[";
    for (int i = 0; i < _args.size(); i++)
    {
        if (i == _args.size() - 1 && _isConcat)
            ret += "|";
        else if (i > 0)
            ret += ", ";
        ret += _args[i]->symbol();
    }
    return ret + "]";
}

string List::value()
{
    string ret = "[";
    for (int i = 0; i < _args.size(); i++)
    {
        if (i == _args.size() - 1 && _isConcat)
            ret += "|";
        else if (i > 0)
            ret += ", ";
        ret += _args[i]->value();
    }
    return ret + "]";
}

bool List::match(Term *term)
{
    Variable *variable = term->getVariable();
    if (variable)
        return variable->match(this);

    List *list = term->getList();
    if (!list)
        return false;
    if (_isConcat && _isConcat != list->_isConcat)
        return preprocess(*this, *list);
    else if (list->_isConcat && _isConcat != list->_isConcat)
        return preprocess(*list, *this);
    return matchList(this, list);
}

List *List::getList()
{
    return this;
}

Term *List::args(int index)
{
    if (index < _args.size())
        return _args[index];
    return nullptr;
}

bool List::preprocess(List concat, List other)
{
    //std::cout << "Enter Preprocess" << std::endl;
    int otherArgSize = other._args.size();
    int concatArgSize = concat._args.size();
    int position = otherArgSize - (otherArgSize - concatArgSize + 1);
    List *concatList;
    if (position >= otherArgSize)
        concatList = new List({}, false);
    else
    {
        concatList = new List({other._args.begin() + position, other._args.end()}, false);
        other._args.erase(other._args.begin() + position, other._args.end());
    }
    other._args.push_back(concatList);
    //std::cout << concatList->value() << std::endl;
    return matchList(&concat, &other);
}

bool List::matchList(List *list, List *other)
{
    if (list->_args.size() != other->_args.size())
        return false;
    for (int i = 0; i < list->_args.size(); i++)
        if (!list->_args[i]->match(other->_args[i]))
            return false;
    return true;
}*/