// Example 10-3. The functions cloneSongList(), appendSong(), and clearSongList()
// songsList.c

#include <stdio.h>
#include <stdlib.h>
#include "songList.h"

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

// Function prototypes for song-list operations:

// The function cloneSongList() duplicates a linked list.
// Argument:     A pointer to the list head of the list to be cloned.
// Return value: The new list. If insufficient memory is available to
//               duplicate the entire list, the new list is empty.

SongList_t cloneSongList( const SongList_t *pList )
{
    SongList_t newSL = { NULL, NULL };       // A new, empty list.

    Cell_t *pCell = pList->pFirst;     // We start with the first list item.
    while ( pCell != NULL && appendSong( &newSL, &pCell->song ))
       pCell = pCell->pNext;

    if ( pCell != NULL )               // If we didn't finish the last item,
      clearSongList( &newSL );         // discard any items cloned.

    return newSL;                      // In either case, return the list head.
}

// The function appendSong() dynamically allocates a new list item,
// copies the given song data to the new object, and appends it to the list.
// Arguments:    A pointer to a Song_t object to be copied, and a pointer
//               to a list to add the copy to.
// Return value: True if successful; otherwise, false.

bool appendSong( SongList_t *pList, const Song_t *pSong )
{
    Cell_t *pCell = calloc( 1, sizeof(Cell_t) );   // Create a new list item.

    if ( pCell == NULL )
       return false;                            // Failure: no memory.

    pCell->song = *pSong;                       // Copy data to the new item.
    pCell->pNext = NULL;

    if ( pList->pFirst == NULL )                // If the list is still empty,
       pList->pFirst = pList->pLast = pCell;    // link a first (and last) item.
    else
    {                                           // If not,
       pList->pLast->pNext = pCell;             // insert a new last item.
       pList->pLast = pCell;
    }

    return true;                                 // Success.
}

// The function clearSongList() destroys all the items in a list.
// Argument: A pointer to the list head.

void clearSongList( SongList_t *pList )
{
    Cell_t *pCell, *pNextCell;
    for ( pCell = pList->pFirst; pCell != NULL; pCell = pNextCell )
    {
       pNextCell = pCell->pNext;
       free( pCell );           // Release the memory allocated for each item.
    }
    pList->pFirst = pList->pLast = NULL;
}

// The printSongList() function prints out each song of the list.
// Argument:     A pointer to the list to be printed.
// Return value: None.

void printSongList( const SongList_t *pList)
{
    Cell_t *pCell = pList->pFirst;
    for( ; pCell != NULL; pCell = pCell->pNext)
        printSong( &pCell->song);
}
