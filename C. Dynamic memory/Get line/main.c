/**
 * Getting line
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Read a line of text from stdin into a dynamically allocated buffer.
 * @details Replace the newline character with a string terminator.
 * @param lenMax The maximum line length to read.
 * @return A pointer to the string read, or NULL if end-of-file was read or if an error occurred.
 */
char* get_line(unsigned int lenMax);

int main()
{
	char* line = NULL;

	while ((line = get_line(128)) != NULL) // If we can read a line,
	{
		puts(line); // process the line,
		free(line); // then release the buffer.
	}

	return EXIT_SUCCESS;
}

char* get_line(unsigned int lenMax)
{
	char* linePtr = malloc(lenMax + 1); // Reverse storage for "worst case."

	if (linePtr != NULL)
	{
		// Read a line of text and replace the newline characters with
		// a string terminator:
		int c = EOF;
		unsigned int i = 0;
		while (i < lenMax && (c = getchar()) != '\n' && c != EOF)
		{
			linePtr[i++] = (char)c;
		}

		linePtr[i] = '\0';

		// If end-of-file before any characters were read, release the whole buffer.
		if (c == EOF && i == 0)
		{
			free(linePtr);
			linePtr = NULL;
		}
		else
		{
			// Otherwise, release the unused portion. i is the string length.
			linePtr = realloc(linePtr, i + 1);
		}
	}

	return linePtr;
}
