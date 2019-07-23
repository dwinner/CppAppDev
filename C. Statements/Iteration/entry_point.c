/**
 * Class average program with sentinel-controlled iteration
 */

#include <stdio.h>

int main(void)
{
   unsigned int counter; // number of grades entered
   int grade; // grade value
   int total; // sum of grades

   float average; // number with decimal point for average

   // initialization phase
   total = 0; // initialize total
   counter = 0; // initialize loop counter

   // processing phase
   // get first grade from user
   printf("%s", "Enter grade, -1 to end: "); // prompt for input
   scanf_s("%d", &grade); // read grade from user

   // loop while sentinel value not yet read from user
   while (grade != -1)
   {
      total = total + grade; // add grade to total
      counter = counter + 1; // increment counter

      // get next grade from user
      printf("%s", "Enter grade, -1 to end: "); // prompt for input
      scanf_s("%d", &grade); // read next grade                  
   }

   // termination phase
   // if user entered at least one grade
   if (counter != 0)
   {
      // calculate average of all grades entered
      average = (float)total / counter; // avoid truncation

      // display average with two digits of precision
      printf("Class average is %.2f\n", average);
   }
   else
   {
      // if no grades were entered, output message
      puts("No grades were entered");
   }
}
