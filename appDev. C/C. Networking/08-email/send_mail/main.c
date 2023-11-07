/**
 * Simple e-mail session to send
 */

#include <stdio.h>
#include <stdbool.h>
#include "send_email.h"

int main()
{
#if defined(_WIN32)
   WSADATA d;
   if (WSAStartup(MAKEWORD(2, 2), &d))
   {
      fprintf(stderr, "Failed to initialize.\n");
      return 1;
   }
#endif

   char hostname[MAX_INPUT];
   get_input("mail server: ", hostname);

   printf("Connecting to host: %s:25\n", hostname);

   SOCKET server = connect_to_host(hostname, "25");
   wait_on_response(server, 220);

   send_format(server, "HELO HONPWC\r\n");
   wait_on_response(server, 250);

   char sender[MAX_INPUT];
   get_input("from: ", sender);
   send_format(server, "MAIL FROM:<%s>\r\n", sender);
   wait_on_response(server, 250);

   char recipient[MAX_INPUT];
   get_input("to: ", recipient);
   send_format(server, "RCPT TO:<%s>\r\n", recipient);
   wait_on_response(server, 250);

   send_format(server, "DATA\r\n");
   wait_on_response(server, 354);

   char subject[MAX_INPUT];
   get_input("subject: ", subject);

   send_format(server, "From:<%s>\r\n", sender);
   send_format(server, "To:<%s>\r\n", recipient);
   send_format(server, "Subject:%s\r\n", subject);

   time_t timer;
   time(&timer);

   struct tm *timeInfo = gmtime(&timer);

   char date[128];
   strftime(date, 128, "%a, %d %b %Y %H:%M:%S +0000", timeInfo);

   send_format(server, "Date:%s\r\n", date);

   send_format(server, "\r\n");

   printf("Enter your email text, end with \".\" on a line by itself.\n");

   while (true)
   {
      char body[MAX_INPUT];
      get_input("> ", body);
      send_format(server, "%s\r\n", body);
      if (strcmp(body, ".") == 0)
      {
         break;
      }
   }

   wait_on_response(server, 250);

   send_format(server, "QUIT\r\n");
   wait_on_response(server, 221);

   printf("\nClosing socket...\n");
   CLOSESOCKET(server);

#if defined(_WIN32)
   WSACleanup();
#endif

   printf("Finished.\n");
   return EXIT_SUCCESS;
}
