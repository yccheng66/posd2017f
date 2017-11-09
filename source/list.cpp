#include "../include/list.h"
#include <iostream>

List::List() : Struct(Atom("."), {})
{
}

List::List(Term *head, List *tail) : Struct(Atom("."), {head, tail})
{
}

List *List::getList()
{
    return this;
}

string List::domainSymbol()
{
    return openParenthesesOutput(true, true);
}

string List::domainValue()
{
    return openParenthesesOutput(false, true);
}

Term *List::head()
{
    const int HEAD = 0;
    if (HEAD < _args.size())
        return _args[HEAD];
    throw string("Accessing head in an empty list");
}

List *List::tail()
{
    const int TAIL = 1;
    if (TAIL < _args.size())
        return _args[TAIL]->getList();
    throw string("Accessing tail in an empty list");
}