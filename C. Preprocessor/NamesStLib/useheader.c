/**
 * use the names_st structure
 */

#include <stdio.h>
#include "names_str.h"

// remember to link with names_st.c

int main(void)
{
   Names candidate;

   getNames(&candidate);
   printf("Let's welcome ");
   showNames(&candidate);
   printf(" to this program!\n");

   return 0;
}
