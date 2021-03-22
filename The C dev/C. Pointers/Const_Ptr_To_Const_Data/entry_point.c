#include <stdio.h>

int main(int argc, char* argv[])
{
   int x = 5;
   int y;

   const int *const ptr = &x;
   /*ptr = 7;*/   // error: *ptr is const; cannot assign new value 
   /*ptr = &y;*/   // error: ptr is const; cannot assign new address

   return 0;
}
