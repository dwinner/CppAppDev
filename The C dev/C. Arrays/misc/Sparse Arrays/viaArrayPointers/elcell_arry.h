//
// Created by Vinevtsev on 8/8/2019.
//

#ifndef VIAARRAYPOINTERS_ELCELL_ARRY_H
#define VIAARRAYPOINTERS_ELCELL_ARRY_H

struct cell
{
   char cell_name[9];
   char formula[128];
} list_entry;

/**
 * Array of 2,600 pointers
 */
struct cell *sheet[2600];

void init_sheet(void);

void store(struct cell *i);

void delete_cell(struct cell *i);

struct cell *find(char *cell_name);

#endif //VIAARRAYPOINTERS_ELCELL_ARRY_H
