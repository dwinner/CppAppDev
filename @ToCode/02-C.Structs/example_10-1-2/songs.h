// The structures Date and Song.
// songs.h

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
