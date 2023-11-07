//
// Created by den on 12/28/2022.
//

#include "error_handling.h"

const char *get_error_text()
{
#if defined(_WIN32)
   static char message[256] = {0};
   FormatMessage(
      FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
      0,
      WSAGetLastError(),
      0,
      message,
      256,
      0);
   char *nl = strrchr(message, '\n');
   if (nl)
   {
      *nl = 0;
   }

   return message;
#else
   return strerror(errno);
#endif
}
