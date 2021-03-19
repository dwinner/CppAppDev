/*
 *  File I/O routines (for the news archive).
 *
 *  ./software/ch11/fileio.c
 *
 *  mtj@cogitollc.com
 *
 */

#include <stdio.h>
#include <unistd.h>
#include "prsconf.h"

extern feedEntryType feed;

#define GRPSTS_FILE	"group.sts"

/*
 *  emitGroupStatus()
 *
 *  Emit the current news counts for each of the active groups.  This
 *  function is called from the HTTP server when the "Mark Read" button
 *  is pushed.
 *
 */

void emitGroupStatus( void )
{
  FILE *fp;
  int  i;

  /* Open the group status file */
  fp = fopen(GRPSTS_FILE, "w");

  /* For each active group within the feed, emit the groups and the last
   * message read for each.
   */
  for (i = 0 ; i < MAX_MONITORS ; i++) {

    if (feed.groups[i].active) {

      fprintf( fp, "%s : %d\n", 
                feed.groups[i].groupName, feed.groups[i].lastMessageRead );

    }

  }

  fclose(fp);

  return;
}


/*
 *  readGroupStatus()
 *
 *  Read the groups file in and load the news message id (last message
 *  read) and store it into the feed.groups array.  This forces the
 *  news monitor to ignore messages that have already been seen.
 *
 */

void readGroupStatus( void )
{
  FILE *fp;
  int  i, curMsg;
  char line[80];

  /* Initialize each of the groups as unread */
  for (i = 0 ; i < MAX_MONITORS ; i++) feed.groups[i].lastMessageRead = -1;

  /* Open the group file for read */
  fp = fopen(GRPSTS_FILE, "r");

  if (fp == NULL) return;

  /* While we've not reached the end of the file, read and parse each line */
  while (!feof(fp)) {

    /* Parse the line to group name and last message read. */
    fscanf( fp, "%s : %d\n", line, &curMsg );

    /* Walk through the active groups list looking for the group so that the
     * last message id can be applied to it.
     */
    for (i = 0 ; i < MAX_MONITORS ; i++) {

      if (feed.groups[i].active) {

        if (!strcmp(feed.groups[i].groupName, line)) {

          feed.groups[i].lastMessageRead = curMsg;
          break;

        }

      }

    }

  }

  return;
}
