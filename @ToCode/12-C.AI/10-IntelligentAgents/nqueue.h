/*
 *  NNTP Queue Types and Symbolics File
 *
 *  ./software/ch11/nqueue.h
 *
 *  mtj@cogitollc.com
 *
 */

#include "nntpc.h"

typedef struct elementStruct *elemPtr;

typedef struct elementStruct {
  int  group;
  int  rank;
  int  msgId;
  char subject[MAX_LG_STRING+1];
  char msgDate[MAX_SM_STRING+1];
  char link[MAX_SM_STRING+1];
  int  shown;
  struct elementStruct *next;
} elementType;
