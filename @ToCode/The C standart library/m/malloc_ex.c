// malloc_ex.c : malloc() example
// -------------------------------------------------------------

#include <stdlib.h>    // void *malloc( size_t size );
#include <stdio.h>
#include <string.h>
//#include <errno.h>

int main()
{
    struct linelink { char *line;
                      struct linelink *next;
    };
    struct linelink *head = NULL, *tail = NULL;

    char buffer[2048];
    FILE *fp_in;

    /* ... 0pen input file ... */
    char filename[] = "malloc.txt";
    if ((fp_in = fopen( filename, "r")) == NULL)
       perror( "Opening input file" );

    while ( NULL != fgets(buffer, sizeof(buffer), fp_in ))
    {
        if ( head == NULL )    /* Chain not yet started; add first link */
        {
            head = tail = malloc( sizeof(struct linelink));
            if ( head != NULL )
            {
               head->line = malloc( strlen( buffer ) + 1 );
               if ( head->line != NULL )
               {  strcpy( head->line, buffer);  head->next = NULL; }
               else
               {  fprintf( stderr, "Out of memory\n" ); return -1; }
            }
            else
            {  fprintf( stderr, "Out of memory\n" ); return -1; }
         }
         else          /* Chain already started; add another link ... */
         {
             puts( "Adding another link ...");
             /* ... */ 
             break;
         }
    }

    return 0;
}
