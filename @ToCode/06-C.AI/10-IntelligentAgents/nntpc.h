/*
 *  Embedded NNTP Client Header File
 *
 *  ./software/ch11/emnntp/emnntp.h
 *
 *  mtj@cogitollc.com
 *
 */

#ifndef NNTPC_H
#define NNTPC_H

#define MAX_LG_STRING	100
#define MAX_SM_STRING	100

typedef struct {
  char *msg;
  int  msgLen;
  int  msgId;
  char subject[MAX_LG_STRING+1];
  char sender[MAX_SM_STRING+1];
  char msgDate[MAX_SM_STRING+1];
  char *bodyStart;
} news_t;

/* Flags for nntpParse */
#define FULL_PARSE	0
#define HEADER_PARSE	1

int  nntpConnect ( char *nntperver );
int  nntpSetGroup ( char *group, int lastMessage );
int  nntpPeek ( news_t *msg, int totalLen );
int  nntpRetrieve ( news_t *msg, int totalLen );
void nntpSkip( void );
int  nntpParse ( news_t *msg, unsigned int flags  );
int  nntpPost ( news_t *msg );
int  nntpDisconnect ( void );

#define ORGANIZATION	"An Internet Development Corporation"

#endif /* NNTPC_H */
