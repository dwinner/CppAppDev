#ifndef CINTEROP_REVERSESTRING_H
#define CINTEROP_REVERSESTRING_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Allocates a new string and initializes it with the reverse of a given string.
 * @param string The source string to reverse.
 * @return A newly allocated buffer filled with the reverse of the given string.
 * @details The returned memory needs to be freed with freeString().
 */
char *reverseString(const char *string);

/**
 * @brief Frees the memory allocated for the given string.
 * @param string The string to deallocate.
 */
void freeString(char *string);

#ifdef __cplusplus
} // matches extern "C"
#endif


#endif //CINTEROP_REVERSESTRING_H
