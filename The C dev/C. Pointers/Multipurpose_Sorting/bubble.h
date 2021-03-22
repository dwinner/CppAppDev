#pragma once

/**
 * @brief Multipurpose bubble sort
 *    @param work Array to sort
 *    @param size Array size
 *    @param compare a pointer to the comparison function that determines sorting order
 */
void bubble(int work[], size_t size, int (*compare)(int a, int b));

/**
* @brief Determine whether elements are out of order for an ascending
*    @param a Element to be greater
*    @param b Element to be lower
*    @return Negative, if b < a, positive otherwise
*/
int ascending(int a, int b);

/**
* @brief Determine whether elements are out of order for a descending
*    @param a Element to be lower
*    @param b Element to be greater
*    @return Positive, if b > a, negative otherwise
*/
int descending(int a, int b);
