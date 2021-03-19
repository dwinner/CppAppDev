/*
 *  Configuration File Parser Types and Symbolics
 *
 *  ./software/ch11/prsconf.h
 *
 *  mtj@cogitollc.com
 *
 */

#ifndef __PRSCONF_H
#define __PRSCONF_H

#define MAX_URL_SIZE            80
#define MAX_SEARCH_ITEM_SIZE    40
#define MAX_SEARCH_STRINGS      10

#define MAX_GROUPS		20

#define MAX_MONITORS    20

#define MAX_LINE        300

#define MAX_NEWS_MSG	(64*1024)

#define MONITOR_PARSE   0
#define FEEDS_PARSE     1
#define GROUPS_PARSE    2

typedef struct {
  int  active;
  char groupName[MAX_URL_SIZE+1];
  int  lastMessageRead;
  char searchString[MAX_SEARCH_STRINGS][MAX_SEARCH_ITEM_SIZE+1];
  int  numSearchStrings;
} groupEntryType;

typedef struct {
  char           url[MAX_URL_SIZE];
  groupEntryType groups[MAX_GROUPS];
} feedEntryType;

typedef struct {
  int  active;
  char url[MAX_URL_SIZE];
  char urlName[MAX_SEARCH_ITEM_SIZE+1];
  int  length;
  int  changed;
  int  shown;
} monitorEntryType;

#endif /* __PRSCONF_H */
