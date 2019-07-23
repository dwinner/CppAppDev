// names_str.c -- define names_st functions
#include <stdio.h>
#include "names_str.h"     // include the revised header file

// function definitions
void getNames(Names* pn)
{
   int i;

   printf("Please enter your first name: ");
   fgets(pn->first, SLEN, stdin);
   i = 0;
   while (pn->first[i] != '\n' && pn->first[i] != '\0')
      i++;
   if (pn->first[i] == '\n')
      pn->first[i] = '\0';
   else
      while (getchar() != '\n')
         continue;

   printf("Please enter your last name: ");
   fgets(pn->last, SLEN, stdin);
   i = 0;
   while (pn->last[i] != '\n' && pn->last[i] != '\0')
      i++;
   if (pn->last[i] == '\n')
      pn->last[i] = '\0';
   else
      while (getchar() != '\n')
         continue;
}

void showNames(const Names* pn)
{
   printf("%s %s", pn->first, pn->last);
}
