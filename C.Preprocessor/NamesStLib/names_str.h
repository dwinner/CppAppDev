// names_str.h --revised with include protection

#ifndef NAMES_H
#define NAMES_H

// constants
#define SLEN 32

// structure declarations
struct namesSt
{
   char first[SLEN];
   char last[SLEN];
};

// typedefs
typedef struct namesSt Names;

// function prototypes
void getNames(Names*);
void showNames(const Names*);

#endif
