// Examples 10-1 and 10-2.
// songs.c

#include <stdio.h>
#include "songs.h"

// The function dateAsString() converts a date from a structure of type
// struct Date into a string of the form mm/dd/yyyy.
// Argument:     A date value of type struct Date.
// Return value: A pointer to a static buffer containing the date string.

const char *dateAsString( struct Date d )
{
    static char strDate[12];
    sprintf( strDate, "%02d/%02d/%04d", d.month, d.day, d.year );
    return strDate;
}

// The printSong() function prints out the contents of a structure
// of type Song_t in a tabular format.
// Argument:     A pointer to the structure object to be printed.
// Return value: None.

void printSong( const Song_t *pSong )
{
    int m = pSong->duration / 60,      // Playing time in minutes
    s = pSong->duration % 60;          // and seconds.

    printf( "----------------------------------------------\n"
            "Title:          %s\n"
            "Artist:         %s\n"
            "Composer:       %s\n"
            "Playing time:   %d:%02d\n"
            "Date:           %s\n",
             pSong->title, pSong->artist, pSong->composer, m, s,
             dateAsString( pSong->published ));
}
