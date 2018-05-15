// Fig. 14.3: fig14_03.c
// Using command-line arguments
#include <stdio.h>

int main(int argc, char *argv[])
{ 
   // check number of command-line arguments
   if (argc != 3) {
      puts("Usage: mycopy infile outfile");
   } 
   else {
      FILE *inFilePtr; // input file pointer

      // try to open the input file 
      if ((inFilePtr = fopen(argv[1], "r")) != NULL) {
         FILE *outFilePtr; // output file pointer

         // try to open the output file 
         if ((outFilePtr = fopen(argv[2], "w")) != NULL) {
            int c; // holds characters read from source file

            // read and output characters
            while ((c = fgetc(inFilePtr)) != EOF) {
               fputc(c, outFilePtr);
            } 

            fclose(outFilePtr); // close the output file
         }  
         else { // output file could not be opened
            printf("File \"%s\" could not be opened\n", argv[2]); 
         } 

         fclose(inFilePtr); // close the input file
      } 
      else { // input file could not be opened
         printf("File \"%s\" could not be opened\n", argv[1]);
      } 
   } 
}
