// cl listing10-1.c
//
// Listing 10-1: GenerateSines
//
// A C program that generates a table of sine values for
// an assembly language lookup table.

#include <stdlib.h>  
#include <stdio.h>
#include <math.h>

int main( int argc, char **argv )
{
    FILE *outFile;
    int angle;
    int r;
    

    // Open the file:
    
    outFile = fopen( "sines.asm", "w" );
    
    // Emit the initial part of the declaration to 
    // the output file:
    
    fprintf
    ( 
        outFile, 
        "Sines:"  // sin(0) = 0
    );
        
    
    // Emit the sines table:
    
    for( angle = 0; angle <= 359; ++angle )
    {
        // Convert angle in degrees to an angle in 
        // radians using:
        //
        // radians = angle * 2.0 * pi / 360.0;
        //
        // Multiply by 1000 and store the rounded 
        // result into the integer variable r.
        
        double theSine = 
            sin
            ( 
                angle * 2.0 * 
                3.14159265358979323846 / 
                360.0 
            );
        r = (int) (theSine * 1000.0); 
        
        
        // Write out the integers eight per line to the 
        // source file.
        // Note: If (angle AND %111) is 0, then angle 
        // is  divisible by 8 and we should output a 
        // newline first.
        
        if( (angle & 7) == 0 )
        {
            fprintf(outFile, "\n\tword\t");
        }
        fprintf( outFile, "%5d", r );
        if ((angle & 7) != 7)
        {
            fprintf(outFile, ",");
        }
        
    } //endfor
    fprintf(outFile, "\n");

    fclose( outFile );
    return 0;
        
} // end main        
