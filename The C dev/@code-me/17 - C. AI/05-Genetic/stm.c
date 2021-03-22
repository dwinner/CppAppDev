/*
 *  Genetic Algorithm Stack Machine (Virtual Computer) Implementation
 *
 *  ./software/ch6/stm.c
 *
 *  mtj@cogitollc.com
 *
 */

#include <stdio.h>
#include "common.h"

#define STACK_DEPTH	25

int stack[STACK_DEPTH];
int stackPointer;

#define ASSERT_STACK_ELEMENTS(x) \
	 if (stackPointer < x) { error = STACK_VIOLATION ; break; }

#define ASSERT_STACK_NOT_FULL \
	 if (stackPointer == STACK_DEPTH) { error = STACK_VIOLATION ; break; }

#define SPUSH(x) (stack[stackPointer++] = x)
#define SPOP     (stack[--stackPointer])
#define SPEEK    (stack[stackPointer-1])


/*
 *  interpretSTM()
 *
 *  This function is the stack machine interpreter.  The program, its
 *  length, and 'argsLength' number of arguments are passed to perform
 *  whatever function is provided within 'program'.  Upon completion,
 *  any error encountered is returned to the caller.  The global stack
 *  'stack' is used to determine the result of the program and to test
 *  what was expected (which determines the fitness).
 *
 */

int interpretSTM(const int *program, int progLength, 
                   const int *args, int argsLength)
{
  int pc = 0;
  int i, error = NONE;
  int a, b;

  stackPointer = 0;

  /* Load the arguments onto the stack */
  for (i = argsLength-1 ; i >= 0 ; i--) {
    SPUSH(args[i]);
  }
  
  /* Execute the program */
  while ((error == NONE) && (pc < progLength)) {

    switch(program[pc++]) {

      case DUP:
        ASSERT_STACK_ELEMENTS(1);
        ASSERT_STACK_NOT_FULL;
        SPUSH(SPEEK);
        break;

      case SWAP:
        ASSERT_STACK_ELEMENTS(2);
        a = stack[stackPointer-1];
        stack[stackPointer-1] = stack[stackPointer-2];
        stack[stackPointer-2] = a;
        break;

      case MUL:
        ASSERT_STACK_ELEMENTS(2);
        a = SPOP; b = SPOP;
        SPUSH(a * b);
        break;

      case ADD:
        ASSERT_STACK_ELEMENTS(2);
        a = SPOP; b = SPOP;
        SPUSH(a + b);
        break;

      case OVER:
        ASSERT_STACK_ELEMENTS(2);
        SPUSH(stack[stackPointer-2]);
        break;

    } /* Switch opcode */

  } /* Loop */

  return(error);
}
