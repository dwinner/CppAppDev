/**
 * Recursive decent parser for Little-C interpreter
 */

#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include "littlec_app.h"

/**
 * @brief points to start of program buffer
 */
char *p_buf;

/**
 * hold environment for longjmp()
 */
jmp_buf e_buf;

int gvar_index; /* index into global variable table */

char *prog;    /* current location in source code */

int lvartos; /* index into local variable stack */

int functos;  /* index to top of function call stack */

int break_occurring; /* loop break is occurring */

/**
 * holds string representation of token
 */
extern char token[80];

int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      printf("Usage: littlec <filename>\n");
      exit(1);
   }

   /* allocate memory for the program */
   if ((p_buf = (char *) malloc(PROG_SIZE)) == NULL)
   {
      printf("Allocation Failure");
      exit(1);
   }

   /* load the program to execute */
   if (!load_program(p_buf, argv[1]))
   {
      exit(1);
   }

   if (setjmp(e_buf))
   {
      /* initialize long jump buffer */
      exit(1);
   }

   gvar_index = 0;  /* initialize global variable index */

   /* set program pointer to start of program buffer */
   prog = p_buf;

   /* find the location of all functions and global variables in the program */
   prescan();

   lvartos = 0;     /* initialize local variable stack index */
   functos = 0;     /* initialize the CALL stack index */
   break_occurring = 0; /* initialize the break occurring flag */

   /* setup call to main() */
   prog = find_func("main"); /* find program starting point */

   if (!prog)
   {
      /* incorrect or missing main() function in program */
      printf("main() not found.\n");
      exit(1);
   }

   prog--; /* back up to opening ( */
   strcpy_s(token, 80, "main");
   call(); /* call main() to start interpreting */

   return 0;
}
