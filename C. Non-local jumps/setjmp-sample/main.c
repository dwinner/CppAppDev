/**
 * setjmp_ex.c : setjmp() - longjmp() example:
 * int setjmp( jmp_buf env );
 * void longjmp( jmp_buf environment, int returnval );
 */

#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

double calculate1(double x);     // Functions defined
double calculate2(double x);     // in calculate.c.

jmp_buf jmp_dest;                 // Destination for longjmp()

int main()
{
   double x = 0, y1, y2;
   int n = 0;

   puts("--- Demonstrating non-local jumps ---\n");

   switch (setjmp(jmp_dest)) // Jump to here for error handling
   {
      case 0:                    // The original setjmp() call
         break;

      case EDOM:                 // Arrived via longjmp() call with EDOM
         puts("Domain error. "
              "Negative numbers are not permitted.");
         break;

      case ERANGE:               // Arrived via longjmp() call with ERANGE
         puts("Range error. "
              "The number you entered is too big.");
         break;

      default:                   // We should never arrive here.
         puts("Unknown error.");
         exit(EXIT_FAILURE);
   }

   printf("Enter a number: ");
   do
   {
      if ((n = scanf("%lf", &x)) < 0)
      {
         // Read in a number.
         exit(EXIT_FAILURE);
      }

      // Read end of file.
      while (getchar() != '\n')
      {
         // Clear the input buffer.
      }

      if (n == 0)
      {
         printf("Invalid entry. Try again: ");
      }
   }
   while (n == 0);

   y1 = calculate1(x);
   y2 = calculate2(x);

   printf("\nResult of Calculation 1: %G\n", y1);
   printf("Result of Calculation 2: %G\n", y2);

   return 0;
}
