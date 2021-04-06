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
   0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
   0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
   0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
   0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
   0.0, 0.0
};

int main(int argc, char* argv[])
{
   double answer;

   const int memorySize = 100;
   char* prgMemory = (char*)malloc(memorySize);
   if (!prgMemory)
   {
      printf("Memory allocation error.\n");
      exit(EXIT_FAILURE);
   }

   /* ��������� ��������� �� ����� ������ ������ */
   do
   {
      program = prgMemory;
      printf("Enter expression: ");
      gets_s(program, memorySize);
      if (!*program)
      {
         break;
      }

      start_evaluation(&answer);
      printf("Result: %.2f\n", answer);
   }
   while (*prgMemory);

   return EXIT_SUCCESS;
}
