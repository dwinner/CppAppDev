/**
 * Functions printRow() and printMatrix()
 */

#include <stdio.h>

#define NCOLS 10                    // The number of columns.
typedef float ROW_t[NCOLS];         // A type for the "row"

// Print one "row" array.
void printRow(const ROW_t pRow)
{
   for (int c = 0; c < NCOLS; ++c)
   {
      printf("%6.2f", pRow[c]);
   }

   putchar('\n');
}

// Print the whole matrix.
void printMatrix(ROW_t *pMat, int nRows)
{
   for (int r = 0; r < nRows; ++r)
   {
      printRow(pMat[r]);           // Print each row.
   }
}

int main()
{
   ROW_t mat[] = {{0.0F, 0.1F},
                  {1.0F, 1.1F, 1.2F},
                  {2.0F, 2.1F, 2.2F, 2.3F}};
   int nRows = sizeof(mat) / sizeof(ROW_t);

   printMatrix(mat, nRows);

   return 0;
}
