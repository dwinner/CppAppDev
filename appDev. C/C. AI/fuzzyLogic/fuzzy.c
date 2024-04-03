#include "fuzzy.h"

fuzzyType fuzzyAnd(fuzzyType lhs, fuzzyType rhs)
{
   assert(lhs >= 0.0);
   assert(lhs <= 1.0);
   assert(rhs >= 0.0);
   assert(rhs <= 1.0);

   return MAX(lhs, rhs);
}

fuzzyType fuzzyOr(fuzzyType lhs, fuzzyType rhs)
{
   assert(lhs >= 0.0);
   assert(lhs <= 1.0);
   assert(rhs >= 0.0);
   assert(rhs <= 1.0);

   return MIN(lhs, rhs);
}

fuzzyType fuzzyNot(fuzzyType fuzzyValue)
{
   assert(fuzzyValue >= 0.0);
   assert(fuzzyValue <= 1.0);

   return (fuzzyType)(1.0 - fuzzyValue);
}
