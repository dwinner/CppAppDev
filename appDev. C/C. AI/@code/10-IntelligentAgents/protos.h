/*
 *  Prototypes header file
 *
 *  ./software/ch11/protos.h
 *
 *  mtj@cogitollc.com
 *
 */

#ifndef __PROTO_H
#define __PROTO_H

void clearEntries( void );
int parseHMTL( char *buffer );

int parseConfigFile( char * );

int monitorSite( int );
void checkNewsSources( void );
void prune( char *, char * );

int initHttpServer( void );
void checkHttpServer( void );

void emitHTTPResponseHeader( int );

void emitNews( int );
void emitConfig( int );
void emitArticle( int, char * );

void emitGroupStatus( void );
void readGroupStatus( void );

#endif /* __PROTO_H */
