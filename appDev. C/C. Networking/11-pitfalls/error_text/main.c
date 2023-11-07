#include <stdio.h>
#include "error_handling.h"

int main()
{

#if defined(_WIN32)
   WSADATA d;
   if (WSAStartup(MAKEWORD(2, 2), &d))
   {
      fprintf(stderr, "Failed to initialize.\n");
      return EXIT_FAILURE;
   }
#endif

   printf("Calling socket() with invalid parameters.\n");
   socket(0, 0, 0);
   const char *errorMessage = get_error_text();
   printf("Last error was: %s\n", errorMessage);
   printf("Finished.\n");

   return EXIT_SUCCESS;
}
