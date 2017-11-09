#include "../include/struct.h"

Struct::Struct(Atom functor, vector<Term *> args) : _functor(functor), _args(args)
{
}

string Struct::symbol()
{
    if (isSpecialStruct())
        return openBracketsOutput(true);
    return openParenthesesOutput(true);
}

string Struct::value()
{
    if (isSpecialStruct())
        return openBracketsOutput(false);
    return openParenthesesOutput(false);
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

int Struct::arity()
{
    return _args.size();
}

bool Struct::isSpecialStruct()
{
    /* the empty list is a special atom [] in prolog and there is no way to
     * use .() to obtain an empty list. so the if statement of size is equal
     * to zero may modify in the future. */
    return (_functor.symbol() == "." && (_args.size() == 2 || _args.size() == 0));
}

string Struct::openParenthesesOutput(bool isSymbol, bool isDomainOutput)
{
    // not a good solution for converting parentheses to brackets here //
    if (_functor.symbol() == "." && _args.size() == 0)
        return "[]";

    string output = _functor.symbol() + "(";
    for (int i = 0; i < _args.size(); i++)
        output += ((i > 0) ? ", " : "") + argOutput(i, isSymbol, isDomainOutput);
    return output + ")";
}

/* can move "tail && tail->getStruct()" into a new method called isStruct 
 * and then replace the tail to structure->args(TAIL) */
string Struct::openBracketsOutput(bool isSymbol)
{
    const int HEAD = 0;
    const int TAIL = 1;
    string output = "[";
    Struct *structure = this;
    Term *tail = args(TAIL);
    for (; tail && tail->getStruct(); structure = tail->getStruct(), tail = structure->args(TAIL))
        output += ((tail != args(TAIL)) ? ", " : "") + structure->argOutput(HEAD, isSymbol);
    if (tail)
        output += ((tail != args(TAIL)) ? ", " : "") + structure->argOutput(HEAD, isSymbol) + "|" + structure->argOutput(TAIL, isSymbol);
    return output + "]";
}

string Struct::argOutput(int index, bool isSymbol, bool isDomainOutput)
{
    if (isDomainOutput && _args[index]->getStruct())
        return _args[index]->getStruct()->openParenthesesOutput(isSymbol, isDomainOutput);
    else if (isSymbol)
        return _args[index]->symbol();
    else
        return _args[index]->value();
}