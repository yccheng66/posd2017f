#include "../include/variable.h"
#include <iostream>

Variable::Variable(string symbol) : _symbol(symbol), _instance(nullptr), _referencer(nullptr), _isVisited(false)
{
}

string Variable::symbol()
{
    return _symbol;
}

string Variable::value()
{
    if (!_instance)
        return _symbol;
    if (_isVisited)
        return getCorrectSymbol();

    _isVisited = true;
    string ret = _instance->value();
    _isVisited = false;
    return ret;
}

bool Variable::match(Term *term)
{
    Variable *variable = term->getVariable();
    if (variable && detectCycle(variable))
        return true;
    return matchInstance(term);
}

Variable *Variable::getVariable()
{
    return this;
}

// Get correct symbol when output //
string Variable::getCorrectSymbol()
{
    Variable *current = this;
    for (; isVariable(current->_instance); current = current->_instance->getVariable())
        ;
    return current->symbol();
}

bool Variable::matchInstance(Term *term)
{
    Variable *current = this;
    for (; isVariable(current->_instance); current = current->_instance->getVariable())
        ;

    if (current->_instance)
        return current->_instance->match(term);
    instantiate(term, current);
    return true;
}

// Instantiate the instance of variable //
void Variable::instantiate(Term *term, Variable *variable)
{
    variable->_instance = term;
    Variable *termVariable = term->getVariable();
    if (termVariable)
        termVariable->_referencer = variable;
}

// Detect if the matcher will cause a cycle or not //
bool Variable::detectCycle(Variable *matcher)
{
    return (matcher == this || isExistInInstances(matcher) || isExistInReferencers(matcher));
}

// Detect if the matcher exists in the instances or not //
bool Variable::isExistInInstances(Variable *matcher)
{
    Term *member = _instance;
    for (; isVariable(member); member = member->getVariable()->_instance)
        if (matcher == member)
            return true;
    return false;
}

// Detect if the matcher exists in the referencers or not //
bool Variable::isExistInReferencers(Variable *matcher)
{
    for (Variable *member = _referencer; member; member = member->_referencer)
        if (matcher == member)
            return true;
    return false;
}

bool Variable::isVariable(Term *term)
{
    return (term && term->getVariable());
}