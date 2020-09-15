// The structures and protypes for a singly linked list of songs.
// songsList.h

#include <stdbool.h>

// The structure Date

struct Date { short month, day, year; };  
const char *dateAsString( struct Date aDate);

// The structure Song to store information about a music recording.

struct Song { char title[64];
              char artist[32];
              char composer[32];
              short duration;           // Playing time in seconds.
              struct Date published;    // Date of publication.
};

typedef struct Song Song_t;       // Song_t is now a synonym for struct Song.
void printSong( const Song_t* pSong);

// Structures for a list head and list items:

typedef struct { struct Cell *pFirst, *pLast; } SongList_t;

typedef struct Cell { struct Song song;            // The record data.
                      struct Cell *pNext;          // A pointer to the next record.
                    } Cell_t;

bool appendSong( SongList_t *pList, const Song_t* pSong);
void clearSongList( SongList_t *pList);
SongList_t cloneSongList( const SongList_t *pList);

void printSongList( const SongList_t* pList);
