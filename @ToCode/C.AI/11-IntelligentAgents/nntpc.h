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


/*
 *  Copyright (c) 2003 Charles River Media.  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or 
 *  without modification, is hereby granted without fee provided 
 *  that the following conditions are met:
 * 
 *    1.  Redistributions of source code must retain the above 
 *        copyright notice, this list of conditions and the 
 *        following disclaimer.
 *    2.  Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the 
 *        following disclaimer in the documentation and/or other 
 *        materials provided with the distribution.
 *    3.  Neither the name of Charles River Media nor the names of 
 *        its contributors may be used to endorse or promote 
 *        products derived from this software without specific 
 *        prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY CHARLES RIVER MEDIA AND CONTRIBUTORS 
 * 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL CHARLES
 * RIVER MEDIA OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */

