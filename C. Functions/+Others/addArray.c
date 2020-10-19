// Example 7-4. Function addArray()
// addArray.c

// addArray() adds each element of the second array to the
// corresponding element of the first (i.e., "array1 += array2", so to speak).
// Arguments: Two arrays of float and their common length.
// Return value: None.

void addArray( register float a1[], register const float a2[], int len )
{
   register float *end = a1 + len;
   for ( ; a1 < end; ++a1, ++a2 )
      *a1 += *a2;
}

#include <stdio.h>

int main()
{
  float fArr1[] = { 1.1F, 2.2F, 3.3F, 4.4F },
        fArr2[] = { 2.2F, 3.3F, 4.4F, 5.5F };
  int len = sizeof(fArr1)/sizeof(*fArr1);

  addArray( fArr1, fArr2, len);     // "fArr1 += farr2"

  for ( int i = 0; i <len; ++i )
     printf("%8.2f", fArr1[i]);
  putchar('\n');    
  return 0;
}
