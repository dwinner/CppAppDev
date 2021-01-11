/**
 *	Using command-line arguments
 */
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

int main(const int argc, char* argv[])
{
	// check number of command-line arguments
	if (argc != 3)
	{
		puts("Usage: mycopy infile outfile");
		return EXIT_SUCCESS;
	}

	FILE* in_file_ptr; // input file pointer

	char* const input_file_name = argv[1];
	char* const output_file_name = argv[2];

	// try to open the input file
	if ((in_file_ptr = fopen(input_file_name, "r")) == NULL)
	{
		printf("File \"%s\" could not be opened\n", input_file_name);
		return EXIT_SUCCESS;
	}

	FILE* out_file_ptr; // output file pointer

	// try to open output file
	if ((out_file_ptr = fopen(output_file_name, "w")) == NULL)
	{
		printf("File \"%s\" could not be opened\n", output_file_name);
		return EXIT_SUCCESS;
	}

	int c; // holds characters read from source file

	// read the output characters
	while ((c = fgetc(in_file_ptr)) != EOF)
	{
		fputc(c, out_file_ptr);
	}

	fclose(out_file_ptr); // close the output file
	fclose(in_file_ptr); // close the input file

	return EXIT_SUCCESS;
}
