// ignore_handler_s_ex.c : ignore_handler_s() example
// -------------------------------------------------------------

#define __STDC_WANT_LIB_EXT1__ 1
#include <stdlib.h>  // void ignore_handler_s( const char * restrict msg,
                     //                        void * restrict ptr, 
                     //                        errno_t error);
#include <string.h>
#include <stdio.h>
#include <errno.h>

// Handle runtime constraint violations using only
// the return value of secure functions.

int main()
{
    char message[20] = "Hello, ",
         name[20];
    set_constraint_handler_s(ignore_handler_s);

    printf("Please enter your name: ");
    if( gets_s( name, sizeof(name)) == NULL)
    { 
       puts("Error: You entered more than 19 characters."); 
       // ...
    }
    else if( strcat_s( message, sizeof(message), name) != 0)
    {
       puts("Error: message array is too small.");
       // ...
    }
    else
       puts( message);

    // ...

    return 0;
}
