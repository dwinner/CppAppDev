#include "fuzzy.h"

FuzzyBoolT fuzzyAnd(FuzzyBoolT lhs, FuzzyBoolT rhs)
{
   assert(lhs >= 0.0);
   assert(lhs <= 1.0);
   assert(rhs >= 0.0);
   assert(rhs <= 1.0);

   return MAX(lhs, rhs);
}

FuzzyBoolT fuzzyOr(FuzzyBoolT lhs, FuzzyBoolT rhs)
{
   assert(lhs >= 0.0);
   assert(lhs <= 1.0);
   assert(rhs >= 0.0);
   assert(rhs <= 1.0);

   return MIN(lhs, rhs);
}

FuzzyBoolT fuzzyNot(FuzzyBoolT fuzzyValue)
{
   assert(fuzzyValue >= 0.0);
   assert(fuzzyValue <= 1.0);

   return (FuzzyBoolT) (1.0 - fuzzyValue);
}
