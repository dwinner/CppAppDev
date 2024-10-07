// c.cpp
//
// Generic C++ driver program to demonstrate
// returning function results from assembly
// language to C++. Also includes a
// "readLine" function that reads a
// string from the user and passes it
// on to the assembly language code.
//
// Need to include stdio.h so this
// program can call "printf" and
// stdio.h so this program can call
// strlen.

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// extern "C" namespace prevents
// "name mangling" by the C++
// compiler.


int main(void)
{
    // Get the assembly language program's title:
    
    int x = strlen("hello world" );
	printf( "length=%d\n", x );
	
}