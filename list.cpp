#include "atom.h"
#include "variable.h"
#include <typeinfo>
#include <iostream>
#include <string>
#include "list.h"
#include "iterator.h"
using std::vector;

Iterator * List::createIterator()
{
  return new ListIterator(this);
}

string List::symbol() const{
    string ret ;
    if(_elements.size()==0 ){
      ret = "[]";
    }
    else{
      ret  = "[";
      std::vector<Term *>::const_iterator it = _elements.begin();
      for( ; it != _elements.end()-1 ; ++it ){
        ret += (*it)->symbol()+", ";
      }
      ret += (*it)->symbol()+"]";
    }
    return ret;
  }
string List::value() const{
    string ret ;
    if(_elements.empty()){
        ret = "[]";
    }
    else{
        ret  = "[";
        std::vector<Term *>::const_iterator it = _elements.begin();
        for( ; it != _elements.end()-1 ; ++it ){
        ret += (*it)->value()+", ";
        }
        ret += (*it)->value()+"]";
}
return ret;
}
bool List::match(Term & term) {
    if(typeid(term) ==  typeid(List)){
        bool ret =true;
        List * ptrls = dynamic_cast<List*>(&term);
        if( _elements.size() != ptrls->_elements.size() ){
        ret = false;
        }
        else{
            Iterator * itSelf = createIterator();
            Iterator * itOther = term.createIterator();
            for(itSelf->first(), itOther->first(); !itSelf->isDone(); itSelf->next(), itOther->next()){
              ret = itSelf->currentItem()->match(*itOther->currentItem());
              if(ret == false)
                  return ret;
            }
            // for(int i = 0 ; i < _elements.size() ;i++ ){
            //     ret = _elements[i]->match(*(ptrls->_elements[i])) ;
            //     if(ret == false)
            //         return ret;
            // }
        }
        return ret;
    }
    return term.match(*this);
}
Term * List::head() const{
    if(_elements.empty())
        throw std::string("Accessing head in an empty list");

    return _elements[0];
}
List * List::tail() const {
    if(_elements.empty())
        throw std::string("Accessing tail in an empty list");
    vector<Term *> _clone_elements;
    _clone_elements.assign(_elements.begin()+1, _elements.end());
    List *ls= new List(_clone_elements) ;
    return ls;
}
