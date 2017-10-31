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

string Variable::getCorrectSymbol()
{
    Variable *variable = this;
    Variable *termVariable = _instance->getVariable();
    for (; termVariable; variable = termVariable, termVariable = variable->_instance->getVariable())
        ;
    return variable->symbol();
}

bool Variable::matchInstance(Term *term)
{
    Variable *variable = this;
    Term *instance = variable->_instance;
    for (; instance && (variable = instance->getVariable()); instance = variable->_instance)
        ;

    if (instance)
    {
        //std::cout << instance->symbol() << std::endl;
        return instance->match(term);
    }
    instantiate(term, variable);
    return true;
}

void Variable::instantiate(Term *term, Variable *variable)
{
    //std::cout << "instantiated variable = " << variable->symbol() << std::endl;
    //std::cout << "instantiated term = " << term->symbol() << std::endl;
    variable->_instance = term;
    Variable *termVariable = term->getVariable();
    if (termVariable)
        termVariable->_referencer = variable;
}

// Detect if the variable will cause a cycle or not //
bool Variable::detectCycle(Variable *variable)
{
    return (variable == this || isExistInInstances(variable) || isExistInReferencers(variable)); // || isExistInInstances(variable) || isExistInReferencers(variable));
}

bool Variable::isExistInInstances(Variable *variable)
{
    Term *instance = _instance;
    Variable *comparison;
    for (; instance && (comparison = instance->getVariable()); instance = comparison->_instance)
        if (comparison == variable)
            return true;
    return false;
}

bool Variable::isExistInReferencers(Variable *variable)
{
    Variable *comparison = _referencer;
    for (; comparison; comparison = comparison->_referencer)
        if (comparison == variable)
            return true;
    return false;
}