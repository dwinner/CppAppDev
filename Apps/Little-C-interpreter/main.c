/**
 * Recursive decent parser for Little-C interpreter
 */

#include <stdio.h>
#include <setjmp.h>

/**
 * Current location in source code
 */
extern char *prog;

/**
 * Points to start of program buffer
 */
extern char *p_buf;

/**
 * Hold environment for longjmp()
 */
extern jmp_buf e_buf;

int main()
{
   printf("Hello, World!\n");
   return 0;
}
