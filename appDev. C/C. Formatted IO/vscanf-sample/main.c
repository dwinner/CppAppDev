// vfscanf_ex.c : vscanf() example
// -------------------------------------------------------------
// int vfscanf( FILE * restrict fp, const char * restrict format,
//              va_list argptr );
// int vscanf( const char * restrict format, va_list argptr );
// int vsscanf( const char * restrict src, const char * restrict format,
//              va_list argptr );

#include <stdio.h>
#include <stdarg.h>

typedef struct
{
   char lastname[20];
   char firstname[20];
   int dob_month;
   int dob_day;
   int dob_year;
} person;

person employee;

// As variable arguments (...) use NULL
// or three int pointers (month, day, year).
int read_person(char *lname, char *fname, ...)
{
   va_list args;
   int count;

   puts("Enter the last name and first name (Example: Smith, Sally)");
   count = scanf("%[^,], %[^\n]", lname, fname);      // Read the name.

       va_start(args, fname);    // Initialize args to start with the argument
   // that follows fname in the function call.
   if (count == 2 && va_arg(args, int*) != NULL)
   {
          va_end(args);
          va_start(args, fname);     // Initialize args again.

      printf("Enter the date of birth. (Example: 9/21/1962)\n");
      count += vscanf("%d/%d/%d", args); // Read date of birth.
   }

#ifdef _DEBUG
      fprintf( stderr, "Read %d fields.\n", count);
#endif // def DEBUG

       va_end(args);

   return count;
}

int main()
{
   person *pEmployee = &employee;
   int result;

   result = read_person(pEmployee->lastname,
                        pEmployee->firstname,
                        &pEmployee->dob_month,
                        &pEmployee->dob_day,
                        &pEmployee->dob_year);
#ifdef _DEBUG
   fprintf( stderr, "Fields read: %s, %s; born %d-%d-%d\n",
             pEmployee->lastname,
             pEmployee->firstname,
             pEmployee->dob_month,
             pEmployee->dob_day,
             pEmployee->dob_year );
#endif // def DEBUG
}
