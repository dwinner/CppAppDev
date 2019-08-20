/**
 *	Этот модуль содержит простой синтаксический анализатор,
 *	который не распознает переменные
 */

#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

char* program;

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
