//
// Created by Vinevtsev on 8/8/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include "elcell_arry.h"

void init_sheet(void)
{
   register int t;
   for (t = 0; t < 2600; ++t)
   {
      sheet[t] = NULL;
   }
}

void store(struct cell *i)
{
   int loc;
   char *p;

   /* compute index given cell name */
   loc = *(i->cell_name) - 'A';   /* column */
   p = &(i->cell_name[1]);
   loc += (atoi(p) - 1) * 26; /* number of rows * row width + column */

   if (loc >= 2600)
   {
      printf("Cell out of bounds.\n");
      return;
   }

   sheet[loc] = i;  /* place pointer in the array */
}

void delete_cell(struct cell *i)
{
   int loc;
   char *p;

   /* compute index given cell name */
   loc = *(i->cell_name) - 'A';   /* column */
   p = &(i->cell_name[1]);
   loc += (atoi(p) - 1) * 26; /* number of rows * row width + column */

   if (loc >= 2600)
   {
      printf("Cell out of bounds.\n");
      return;
   }

   if (!sheet[loc])  /* don't free a null pointer */
   {
      return;
   }

   free(sheet[loc]); /* return memory to system */
   sheet[loc] = NULL;
}

struct cell *find(char *cell_name)
{
   int loc;
   char *p;

   /* compute index given name */
   loc = *(cell_name) - 'A';   /* column */
   p = &(cell_name[1]);
   loc += (atoi(p) - 1) * 26; /* number of rows * row width + column */

   if (loc >= 2600 || !sheet[loc]) /* no entry in that cell */
   {
      printf("Cell not found.\n");
      return NULL;   /* not found */
   }
   else
   {
      return sheet[loc];
   }
}
