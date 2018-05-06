/**
 * Using atomic read/write operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>

int main()
{
   _Atomic int hogs;
   atomic_store(&hogs, 12);

   return EXIT_SUCCESS;
}