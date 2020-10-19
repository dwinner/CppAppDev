// Example 2-2. Illustrating the precision of type float  
// precision.c

#include <stdio.h>
#include <float.h>

int main()
{
   puts("\nCharacteristics of the type float\n");

   printf("Storage size: %llu bytes\n"
          "Smallest positive value: %E\n"
          "Greatest positive value: %E\n"
          "Precision: %d decimal digits\n",
          sizeof(float), FLT_MIN, FLT_MAX, FLT_DIG);

   puts("\nAn example of float precision:\n");
   double d_var = 12345.6;          // A variable of type double.
   float f_var = (float) d_var;      // Initializes the float
   // variable with the value of d_var.
   printf("The floating-point number    "
          "%18.10f\n", d_var);
   printf("has been stored in a variable\n"
          "of type float as the value   "
          "%18.10f\n", f_var);
   printf("The rounding error is        "
          "%18.10f\n", d_var - f_var);

   return 0;
}
