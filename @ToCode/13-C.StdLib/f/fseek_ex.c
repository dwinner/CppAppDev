// fseek_ex.c : fseek() example
// -------------------------------------------------------------

#include <stdio.h>   // int fseek( FILE *fp, long offset, int origin );

typedef struct { long id;
                 double value;
               } record;

// void writeRecords();

int main()
{
    FILE *fp;
    record cur_rec = (record) { 0, 0.0 };
    int reclength_file = sizeof(record);
    long seek_id = 123L;

    if ( (fp = fopen("records", "rb")) == NULL)
        perror( "Unable to open records file" );
    else do
    {
        if ( 1 > fread( &cur_rec.id, sizeof (long), 1, fp ))
        {
           fprintf( stderr, "Record with ID %ld not found.\n", seek_id );
           break;
        }
        else                                      // Skip rest of record
           if ( fseek( fp, reclength_file - sizeof(long), 1 ) )
           {
              perror( "fseek failed" );
              break;
           }
    } while ( cur_rec.id != seek_id );

    if( cur_rec.id == seek_id )
        printf( "Record with ID %ld found.\n", seek_id );
   
    return 0;
}
/*
void writeRecords()
{
    FILE *fp;
    record someRecords[] = {  { 101L, 10.0 }, { 123L, 20.0 },{ 146L, 30.0 } };
    size_t n = sizeof( someRecords) / sizeof( *someRecords);

    if ((fp = fopen("records", "wb")) == NULL)
       perror( "Unable to open records file" );
    else 
    {
       if( fwrite( someRecords, sizeof(record), n, fp) < n) 
          perror( "Unable to write records" );
       fclose(fp);
    }
}
*/
