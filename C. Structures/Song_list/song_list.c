#include <stdlib.h>
#include <stdio.h>
#include "song_list.h"

const char *dateAsString(struct Date aDate)
{
   static char strDate[12];
   sprintf(strDate, "%02d/%02d/%04d", aDate.month, aDate.day, aDate.year);

   return strDate;
}

void printSong(const Song_t *pSong)
{
   int m = pSong->duration / 60,      // Playing time in minutes
   s = pSong->duration % 60;          // and seconds.

   printf("----------------------------------------------\n"
          "Title:          %s\n"
          "Artist:         %s\n"
          "Composer:       %s\n"
          "Playing time:   %d:%02d\n"
          "Date:           %s\n",
          pSong->title, pSong->artist, pSong->composer, m, s,
          dateAsString(pSong->published));
}

bool appendSong(SongList_t *pList, const Song_t *pSong)
{
   Cell_t *pCell = calloc(1, sizeof(Cell_t));   // Create a new list item.

   if (pCell == NULL)
   {
      return false;  // Failure: no memory.
   }

   pCell->song = *pSong;  // Copy data to the new item.
   pCell->pNext = NULL;

   if (pList->pFirst == NULL)   // If the list is still empty,
   {
      pList->pFirst = pList->pLast = pCell;   // link a first (and last) item.
   }
   else  // If not
   {
      pList->pLast->pNext = pCell; // insert a new last item.
      pList->pLast = pCell;
   }

   return true;
}

void clearSongList(SongList_t *pList)
{
   Cell_t *pCell, *pNextCell;

   for (pCell = pList->pFirst; pCell != NULL; pCell = pNextCell)
   {
      pNextCell = pCell->pNext;
      free(pCell);   // // Release the memory allocated for each item.
   }

   pList->pFirst = pList->pLast = NULL;
}

SongList_t cloneSongList(const SongList_t *pList)
{
   SongList_t newSongList = {NULL, NULL}; // A new, empty list.

   Cell_t *pCell = pList->pFirst;  // We start with the first list item.

   while (pCell != NULL && appendSong(&newSongList, &pCell->song))
   {
      pCell = pCell->pNext;
   }

   if (pCell != NULL)  // If we didn't finish the last item,
   {
      clearSongList(&newSongList);  // discard any items cloned.
   }

   return newSongList;  // In either case, return the list head.
}

void printSongList(const SongList_t *pList)
{
   Cell_t *pCell = pList->pFirst;
   for (; pCell != NULL; pCell = pCell->pNext)
   {
      printSong(&pCell->song);
   }
}
