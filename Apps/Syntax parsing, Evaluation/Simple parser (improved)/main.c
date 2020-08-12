/**
 * This module contains the recursive
 * descent parser that recognizes variables.
 * 
 * Examples:
 * A = 10 / 4
 * A - B
 * C = A * (F - 21)
 */

#include <stdlib.h>
#include <stdio.h>
#include "eval_parser.h"

char* program;

double vars[VARIABLE_NUMBER] =
{
   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
   0.0, 0.0, 0.0, 0.0, 0.0, 0.0
};

int main(int argc, char* argv[])
{
   double answer;

   const int memory_size = 100;
   char* p = (char*)malloc(memory_size);
   if (!p)
   {
      printf("Memory allocation error.\n");
      exit(EXIT_FAILURE);
   }

   /* Обработка выражений до ввода пустой строки */
   do
   {
      program = p;
      printf("Enter expression: ");
      gets_s(program, memory_size);
      if (!*program)
      {
         break;
      }

      start_evaluation(&answer);
      printf("Result: %.2f\n", answer);
   }
   while (*p);

   return EXIT_SUCCESS;
}
