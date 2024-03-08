/**
 * Find the keys using a depth-first search.
 */

#include <stdlib.h>
#include "finder.h"

int main()
{
   char from[20] = "front_door";
   char to[20] = "keys";

   setup();
   isKeys(from, to);
   route();

   return EXIT_SUCCESS;
}
