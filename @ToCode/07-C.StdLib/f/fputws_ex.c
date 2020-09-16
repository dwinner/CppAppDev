// fputws_ex.c : fputws() example
// -------------------------------------------------------------

#include <wchar.h>   // int fputws( const wchar_t * restrict ws,
                     //              FILE * restrict fp );
#include <stdio.h>
#include <locale.h>

int main()
{
    FILE *fpw;
    char fname_wide[] = "widetest.txt";
    int widemodeflag = 1;
    int result;

    if ( setlocale( LC_CTYPE, "" ) == NULL)
    {
       fwprintf( stderr, L"Sorry, couldn't change to the system's native locale.\n");
       return -1;
    }
    wchar_t widestring[] = L"How many umlauts are there in Fahrvergnügen?\n";

    if ((fpw = fopen(fname_wide, "a")) == NULL)
    {    perror( "Opening output file" ); return -1; }

    // Set file to wide-character orientation:
    widemodeflag = fwide(fpw, widemodeflag);
    if ( widemodeflag <= 0 )
    {
       fprintf(stderr, "Unable to set output file %s to wide characters\n",
                       fname_wide);
       (void)fclose(fpw);
       return -1;
    }
    // Write wide-character string to the file:
    result = fputws( widestring, fpw );
    if ( result < 0 )
    {
       fprintf(stderr, "Error on writing file %s.\n", fname_wide);
       return -1;
    }
    return 0;
}
