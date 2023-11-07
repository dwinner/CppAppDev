/*
 *  Fuzzy Logic Basic Operators
 *
 *  ./software/ch9/fuzzy.c
 *
 *  mtj@cogitollc.com
 *
 */

#include <assert.h>
#include "fuzzy.h"

#define MAX(a,b)	((a>b) ? a : b)
#define MIN(a,b)	((a<b) ? a : b)

/*
 *  fuzzyAnd()
 *
 *  Fuzzy version of the AND operator.
 *
 */

fuzzyType fuzzyAnd( fuzzyType a, fuzzyType b )
{
  assert(a >= 0.0);
  assert(a <= 1.0);
  assert(b >= 0.0);
  assert(b <= 1.0);

  return MAX(a,b);
}


/*
 *  fuzzyOr()
 *
 *  Fuzzy version of the OR operator.
 *
 */

fuzzyType fuzzyOr( fuzzyType a, fuzzyType b )
{
  assert(a >= 0.0);
  assert(a <= 1.0);
  assert(b >= 0.0);
  assert(b <= 1.0);

  return MIN(a,b);
}


/*
 *  fuzzyNot()
 *
 *  Fuzzy version of the NOT operator.
 *
 */

fuzzyType fuzzyNot( fuzzyType a )
{
  assert(a >= 0.0);
  assert(a <= 1.0);

  return( 1.0 - a );
}
