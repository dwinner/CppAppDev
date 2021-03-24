// strcspn_ex.c : strcspn() example
// -------------------------------------------------------------
// int strcspn( const char *s1, const char *s2 );

#include <string.h>
#include <stdio.h>

int main()
{
   char *path = "/usr/local/bin:/usr/bin:/bin:/usr/bin/X11:/usr/games";
   int separator;
   char *basename = "aprogram";
   char fullname[1024] = "";

   separator = strcspn(path, ":");  // Obtain the index of the first colon.
   strncpy(fullname, path, separator);
   fullname[separator] = '\0';        // Terminate the copied string fragment.
   strncat(fullname, "/", sizeof(fullname) - strlen(fullname) - 1);
   strncat(fullname, basename, sizeof(fullname) - strlen(fullname) - 1);

   puts(fullname);

   return 0;
}
