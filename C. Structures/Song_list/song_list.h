#ifndef SONG_LIST_SONG_LIST_H
#define SONG_LIST_SONG_LIST_H

// The structures and prototypes for a singly linked list of songs
#include <stdbool.h>

/**
 * The Date structure
 */
struct Date
{
   short month, day, year;
};

/**
 * The Song structure to store information about a music recording
 */
struct Song
{
   char title[64];
   char artist[32];
   char composer[32];
   short duration;         // Playing time in seconds
   struct Date published;  // Date of publication
};

/**
 * Song_t is now a synonym for struct Song
 */
typedef struct Song Song_t;

// Structures for a list head and list items

typedef struct Cell
{
   struct Song song;    // The record data
   struct Cell *pNext;  // A pointer to the next record
} Cell_t;

typedef struct
{
   struct Cell *pFirst, *pLast
} SongList_t;

/**
 * The function dateAsString() converts a date from a structure of type
 * struct Date into a string of the form mm/dd/yyyy
 * @param aDate A date value of type struct Date
 * @return A pointer to a static buffer containing the date string
 */
const char *dateAsString(struct Date aDate);

/**
 * The printSong() function prints out the contents of a structure
 * of type Song_t in a tabular format
 * @param pSong A pointer to the structure object to be printed
 */
void printSong(const Song_t *pSong);

/**
 * The function appendSong() dynamically allocates a new list item,
 * copies the given song data to the new object, and appends it to the list
 * @param pList A pointer to a Song_t object to be copied
 * @param pSong A pointer to a list to add the copy to
 * @return true if successful; otherwise, false
 */
bool appendSong(SongList_t *pList, const Song_t *pSong);

/**
 * The function clearSongList() destroys all the items in a list
 * @param pList A pointer to the list head
 */
void clearSongList(SongList_t *pList);

/**
 * The function cloneSongList() duplicates a linked list.
 * @param pList A pointer to the list head of the list to be cloned.
 * @return  The new list. If insufficient memory is available to
 *          duplicate the entire list, the new list is empty.
 */
SongList_t cloneSongList(const SongList_t *pList);

/**
 * The printSongList() function prints out each song of the list.
 * @param pList A pointer to the list to be printed.
 */
void printSongList(const SongList_t *pList);

#endif //SONG_LIST_SONG_LIST_H
