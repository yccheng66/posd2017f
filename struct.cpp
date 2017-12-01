#include "struct.h"
#include "iterator.h"
Iterator * Struct::createIterator()
{
  return new StructIterator(this);
}
