/**
 * Using the song list  structure
 */

#include <stdio.h>
#include <stdlib.h>
#include "song_list.h"

Song_t mySong =
   {
      "What it is",
      "Aubrey Haynie; Mark Knopfler",
      "Mark Knopfler",
      297,
      {
         9,
         26,
         2000
      }
   };

Song_t aSong =
   {
      .title =  "I've Just Seen a Face",
      .composer = "John Lennon; Paul McCartney",
      127
   };

int main()
{
   SongList_t
      mySongs = {NULL, NULL},
      yourSongs = {NULL, NULL};

   if (!appendSong(&mySongs, &mySong) || !appendSong(&mySongs, &aSong))
      fprintf(stderr, "songList: Insufficient memory.\n"), exit(1);

//    printSongList( &mySongs);

   yourSongs = cloneSongList(&mySongs);
   puts("\nThe cloned list:");
   printSongList(&yourSongs);

   if (!appendSong(&mySongs, &(Song_t) {"Havana Club", "Ottmar Liebert", "", 251}))
      fprintf(stderr, "songList: Insufficient memory.\n"), exit(1);

   puts("\nThe list mySongs with a new song:");
   printSongList(&mySongs);

   clearSongList(&mySongs);
   puts("\nNow the list mySongs is empty!");
   printSongList(&mySongs);

   return 0;
}
