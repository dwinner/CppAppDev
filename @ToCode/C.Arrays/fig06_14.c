// Fig. 6.14: fig06_14.c
// Using the const type qualifier with arrays.
#include <stdio.h>

void tryToModifyArray(const int b[]); // function prototype

// function main begins program execution
int main(void)
{
   int a[] = { 10, 20, 30 }; // initialize array a

   tryToModifyArray(a);

   printf("%d %d %d\n", a[0], a[1], a[2]);
}

// in function tryToModifyArray, array b is const, so it cannot be
// used to modify its argument array in the caller.                
void tryToModifyArray(const int b[])                            
{                                                                 
   b[0] /= 2; // error                                    
   b[1] /= 2; // error                                    
   b[2] /= 2; // error                                    
} 
