#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <stdlib.h>

#ifndef SIZE
#define SIZE 10
#endif

/**
 * \brief Sorts the array via the merging
 * \param array Array to sort
 * \param length Array size
 */
void merge_sort(int array[], size_t length);

/**
 * \brief Display elements in array
 * \param array Array to print
 * \param length Array length
 */
void display_elements(int array[], size_t length);

#endif // MERGE_SORT_H
