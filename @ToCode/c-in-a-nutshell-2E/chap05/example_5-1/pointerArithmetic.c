// Exampple 5-1. Pointer Arithmetic
// pointerArithmetic.c : 
// Using a pointer to move through the elements in an array 

#include <stdio.h>

int main()
{
  double dArr[5] = { 0.0, 1.1, 2.2, 3.3, 4.4 },  // Initialize an array and
  *dPtr = dArr;                                  // a pointer to its first
                                                 // element.
  int i = 0;                         // An index variable.
  dPtr = dPtr + 1;                   // Advance dPtr to the second element.
  dPtr = 2 + dPtr;                   // Addends can be in either order.
                                     // dPtr now points to dArr[3].

  printf( "%.1f\n", *dPtr );         // Print the element referenced by dPtr.
  printf( "%.1f\n", *(dPtr -1) );    // Print the element before that, without
                                     // modifying the pointer dPtr.
  i = dPtr - dArr;                   // Result: the index of the
                                     // array element that dPtr points to.
  printf( "%.d\n", i );              // Print the index (3).

  return 0;
}
