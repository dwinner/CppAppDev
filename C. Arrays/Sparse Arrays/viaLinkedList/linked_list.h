#ifndef VIALINKEDLIST_LINKED_LIST_H

#define VIALINKEDLIST_LINKED_LIST_H

struct cell
{
   char cell_name[9];   /* cell name, e.g., A1, B34 */
   char formula[128];   /* info, e.g. 10/B2 */
   struct cell *next;   /* pointer to the next entry */
   struct cell *prior;  /* pointer to the previous record */
};

/**
 * Store cells in sorted order
 *
 * @param i pointer to a new cell to insert
 * @param start Start (can be modified)
 * @param last Last (can be modified)
 */
void dlsStore(struct cell *i, struct cell **start, struct cell **last);

/**
 * Delete cell
 *
 * @param cell_name Cell name
 * @param start Start (can be modified)
 * @param last Last (can be modified)
 */
void deleteCell(char *cell_name, struct cell **start, struct cell **last);

/**
 * Find cell by name
 *
 * @param cell_name Cell name
 * @param start Search from the start
 * @return Found cell
 */
struct cell *findCell(char *cell_name, struct cell *start);

#endif //VIALINKEDLIST_LINKED_LIST_H
