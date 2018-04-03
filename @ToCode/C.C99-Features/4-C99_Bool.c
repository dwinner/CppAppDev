// Fig. E.5: figE_05.c
// Using the type bool and the values true and false in C99
#include <stdio.h>
#include <stdbool.h> // allows bool, true, and false

bool isEven(int number); // function prototype

int main(void)
{
   // loop for 2 inputs
   for (int i = 0; i < 2; ++i) {
      printf("Enter an integer: ");
      int input; // value entered by user
      scanf("%d", &input);

      bool valueIsEven = isEven(input); // determine if input is even

      // determine whether input is even
      if (valueIsEven) {
         printf("%d is even\n\n", input);
      } 
      else {
         printf("%d is odd\n\n", input);
      } 
   } 
} 

// isEven returns true if number is even
bool isEven(int number)
{
   if (number % 2 == 0) { // is number divisible by 2?
      return true;
   }
   else {
      return false;
   }
} 
