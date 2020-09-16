/*
 *  NNTP Message Parsers Prototypes
 *
 *  ./software/ch11/parsers.h
 *
 *  mtj@cogitollc.com
 *
 */

#ifndef PARSERS_H
#define PARSERS_H

#include "nntpc.h"

int parseEntry( news_t *news, const char *searchString, char *dest );
int fixAddress ( char *address );
int findBody( news_t *news );

#endif /* PARSERS_H */
