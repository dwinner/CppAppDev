/**
 * Little C interpreter
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "littlec.h"

int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      printf("Usage: littlec <filename>\n");
      exit(EXIT_FAILURE);
   }

   /* allocate memory for the program */
   if ((p_buf = (char *) malloc(PROG_SIZE)) == NULL)
   {
      printf("Allocation Failure");
      exit(EXIT_FAILURE);
   }

   /* load the program to execute */
   if (!load_program(p_buf, argv[1]))
   {
      exit(EXIT_FAILURE);
   }

   /* initialize long jump buffer */
   if (setjmp(e_buf))
   {
      exit(EXIT_FAILURE);
   }

   gvar_index = 0; /* initialize global variable index */

   /* set program pointer to start of program buffer */
   prog = p_buf;
   prescan(); /* find the location of all functions and global variables in the program */

   lvartos = 0; /* initialize local variable stack index */
   functos = 0; /* initialize the call stack index */
   break_occuring = 0; /* initialize the break occuring flag */

   /* setup call to main() */
   prog = find_func("main"); /* find program starting point */
   if (!prog) /* incorrect or missing main() function in program */
   {
      printf("main() isn't found.\n");
      exit(EXIT_FAILURE);
   }

   prog--; /* back up to opening ( */
   strcpy(token, "main");
   call(); /* call main() to start interpreting */

   return EXIT_SUCCESS;
}
