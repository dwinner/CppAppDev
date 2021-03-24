/*
 *  News Generation Functions.
 *
 *  ./software/ch11/newsmon.c
 *
 *  mtj@cogitollc.com
 *
 */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "prsconf.h"
#include "protos.h"
#include "nntpc.h"
#include "nqueue.h"

extern feedEntryType feed;

elementType head;


/*
 *  clearEntries()
 *
 *  This function clears the news entires and records for monitored web
 *  sites.  It's called when the user pushes the 'clear-entries' button
 *  on the served main page.
 *
 */

void clearEntries( void )
{
  elementType *walker = &head;
  elementType *temp;
  int i;

  extern monitorEntryType monitors[];

  /* Clear the news chain (for items that have been viewed) */
  while (walker->next) {

    if (walker->next->shown) {
      temp = walker->next;
      walker->next = walker->next->next;
      free(temp);
    } else {
      walker = walker->next;
    }

  }

  /* Clear sites to be monitored (that have been seen) */
  for (i = 0 ; i < MAX_MONITORS ; i++) {

    if ((monitors[i].active) && (monitors[i].shown)) {
      monitors[i].changed = 0;
      monitors[i].shown = 0;
    }

  }

  emitGroupStatus();

}


/*
 *  showNewsItems()
 *
 *  This debug function is used to emit the current news items as stored
 *  on the news list.
 *
 */

void showNewsItems( void )
{
  elementType *walker = &head;

  printf("Current news items:\n\n");

  while (walker->next) {

    printf("id      : %d\n", walker->next->msgId);
    printf("rank    : %d\n", walker->next->rank);
    printf("group   : %d\n", walker->next->group);
    printf("subject : %s\n", walker->next->subject);
    printf("date    : %s\n\n", walker->next->msgDate);

    walker = walker->next;

  }

}


/*
 *  insertNewsItem()
 *
 *  This function inserts a news item onto the list in rank order (based upon
 *  the count argument).
 *
 */

void insertNewsItem( int group, int count, news_t *news )
{
  elementType *walker = &head;
  elementType *newElement;

  /* Create and initialize the newElement structure from the passed news */
  newElement = (elementType *)malloc(sizeof(elementType));

  newElement->group = group;
  newElement->rank = count;
  newElement->msgId = news->msgId;
  strncpy( newElement->subject, news->subject, MAX_LG_STRING );
  strncpy( newElement->msgDate, news->msgDate, MAX_SM_STRING );
  newElement->shown = 0;
  sprintf(newElement->link, "art%d_%d", group, news->msgId);
  newElement->next = (elementType *)NULL;

  /* Walk through the news list and identify where to insert this item */
  while (walker) {

    /* If no next element, add new element to the end */
    if (walker->next == NULL) {
      walker->next = newElement;
      break;
    }

    /* Otherwise, insert in rank order (descending) */
    if (walker->next->rank < newElement->rank) {
      newElement->next = walker->next;
      walker->next = newElement;
      break;
    }

    walker = walker->next;

  }

  return;
}


/*
 *  testNewsItem()
 *
 *  Given a news item, parsed by the NNTP API, check to see how many of the
 *  search keywords are present in the subject.  If keywords are found, or
 *  the user configured no search items for this group, insert it into the
 *  news list.
 *
 */

void testNewsItem( int group, news_t *news )
{
  int i, count=0;
  char *cur;

  /* If search strings were defined... */
  if (feed.groups[group].numSearchStrings > 0) {

    /* For each of the search strings, check it against the subject of the
     * news item.  If found, increment count.
     */
    for ( i = 0 ; i < feed.groups[group].numSearchStrings ; i++ ) {

      cur = strstr( news->subject, feed.groups[group].searchString[i] );

      if (cur) count++;

    }

  } else {

    /* No search strings were defined, set count to non-zero so that the
     * news item will be inserted into the list.
     */
    count = -1;

  }

  /* If count is non-zero, insert the news item into the list */
  if (count) {

    insertNewsItem( group, count, news );

  }

  return;
}


/*
 *  checkGroup()
 *
 *  This high level function connects to the NNTP server, and checks to see
 *  if any messages are available.  If so, it runs each of the messages
 *  through the testNewsItem routine to see if they should be inserted onto
 *  the news list.
 *
 */

void checkGroup( int group )
{
  int result, count, index = 0;
  char fqdn[80];
  news_t news;

  /* Create a news item in preparation for using the NNTP API. */
  news.msg = (char *)malloc(MAX_NEWS_MSG+1);
  bzero( news.msg, MAX_NEWS_MSG+1 );
  news.msgLen = MAX_NEWS_MSG;

  /* Prune the URL to a simple FQDN */
  prune( feed.url, fqdn );

  printf("checkGroup called %s\n", fqdn);

  /* Connect to the defined NNTP server */
  count = nntpConnect( fqdn );

  if (count == 0) {

    /* Set to the defined group */
    count = nntpSetGroup( feed.groups[group].groupName, 
                          feed.groups[group].lastMessageRead );

    printf("Group set to %s (last read %d)\n", 
        feed.groups[group].groupName, feed.groups[group].lastMessageRead);

    index = 0;

    /* Only search through 100 messages on each invocation.  This is done
     * because during the time we're searching here, the user will be unable
     * to connect to the HTTP server (single thread of control).
     */
    if (count > 100) count = 100;

    while (count-- > 0) {

      /* Peek at the message (don't retrieve the body, just the headers) */
      result = nntpPeek( &news, MAX_NEWS_MSG );

      if (result > 0) {

        /* Parse the message headers */
        result = nntpParse( &news, HEADER_PARSE );

        if (result == 0) {

          testNewsItem( group, &news );

        } 

      }

      feed.groups[group].lastMessageRead = news.msgId;
      nntpSkip();

    }

  }

  free( news.msg );

  /* Disconnect from the NNTP server */
  nntpDisconnect();

  printf("Disconnected\n");

  return;
}


/*
 *  checkNewsSources()
 *
 *  Main function for checking the news server.
 *
 */

void checkNewsSources( void )
{
  int i;

  extern feedEntryType feed;

  /* For each of the active groups within the feed, call checkGroup to see
   * if any new messages are available that meet the user's search criteria.
   */
  for (i = 0 ; i < MAX_GROUPS ; i++) {

    if ( feed.groups[i].active ) {

      checkGroup( i );

    }

  }

  return;
}
