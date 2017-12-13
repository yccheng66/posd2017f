#include "struct.h"
#include "iterator.h"
Iterator * Struct::createIterator()
{
  return new StructIterator(this);
}

// bool Struct::match( Term &term ){
//   Struct *s = dynamic_cast<Struct*>(&term);
//   if( s ){
//     if( _name.symbol() != s->_name.symbol() ) return false;
//     if(arity() != s->arity())return false;
//     Iterator *s1 = createIterator();
//     Iterator *s2 = term.createIterator();
//     for( s1->first(), s2->first(); !s1->isDone() ; s1->next(), s2->next() ){
//       if( !s1->currentItem()->match( *s2->currentItem() ))
//         return false;
//     }
//     return true;
//   }
//   return Term::match(term);
// }

// string Struct::symbol() const {
//   if(_args.empty())
//   return  _name.symbol() + "()";
//   string ret = _name.symbol() + "(";
//   std::vector<Term *>::const_iterator it = _args.begin();
//   for (; it != _args.end()-1; ++it)
//     ret += (*it)->symbol()+", ";
//   ret  += (*it)->symbol()+")";
//   return ret;
// }
