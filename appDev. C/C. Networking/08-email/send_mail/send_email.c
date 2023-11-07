//
// Created by ubuntu on 12/21/22.
//

#include "send_email.h"
#include "network.h"
#include <ctype.h>
#include <stdarg.h>

void get_input(const char *aPrompt, char *const aBuffer)
{
   printf("%s", aPrompt);

   aBuffer[0] = 0;
   fgets(aBuffer, MAX_INPUT, stdin);
   const size_t readLen = strlen(aBuffer);
   if (readLen > 0)
   {
      aBuffer[readLen - 1] = 0;
   }
}

void send_format(SOCKET aServer, const char *aText, ...)
{
   char buffer[MAX_BUFFER_SIZE];
   va_list args;
   va_start(args, aText);
   vsprintf(buffer, aText, args);
   va_end(args);

   send(aServer, buffer, strlen(buffer), 0);

   printf("C: %s", buffer);
}

int parse_response(const char *const response)
{
   const char *poResp = response;
   if (!poResp[0] || !poResp[1] || !poResp[2])
   {
      return 0;
   }

   for (; poResp[3]; ++poResp)
   {
      if ((poResp == response || poResp[-1] == '\n')
          && isdigit(poResp[0])
          && isdigit(poResp[1])
          && isdigit(poResp[2])
          && poResp[3] != '-'
          && strstr(poResp, "\r\n"))
      {
         return (int) strtol(poResp, 0, 10);
      }
   }

   return 0;
}

void wait_on_response(const SOCKET aServer, const int anExpectingCode)
{
   char response[MAX_RESPONSE + 1];
   char *poResp = response;
   char *end = response + MAX_RESPONSE;
   int code = 0;

   do
   {
      int bytesReceived = recv(aServer, poResp, end - poResp, 0);
      if (bytesReceived < 1)
      {
#ifndef NDEBUG
         fprintf(stderr, "Connection dropped.\n");
#endif

         exit(1);
      }

      poResp += bytesReceived;
      *poResp = 0;
      if (poResp == end)
      {
#ifndef NDEBUG
         fprintf(stderr, "Server response too large:\n");
         fprintf(stderr, "%s", response);
#endif

         exit(EXIT_FAILURE);
      }

      code = parse_response(response);

   } while (code == 0);

   if (code != anExpectingCode)
   {
#ifndef NDEBUG
      fprintf(stderr, "Error from server:\n");
      fprintf(stderr, "%s", response);
#endif

      exit(EXIT_FAILURE);
   }

#ifndef NDEBUG
   printf("S: %s", response);
#endif
}

SOCKET connect_to_host(const char *const hostname, const char *const port)
{
   static const int bufferLen = 100;

#ifndef NDEBUG
   printf("Configuring remote address...\n");
#endif

   struct addrinfo hints;
   memset(&hints, 0, sizeof(hints));
   hints.ai_socktype = SOCK_STREAM;
   struct addrinfo *peerAddr;
   if (getaddrinfo(hostname, port, &hints, &peerAddr))
   {
#ifndef NDEBUG
      fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
#endif

      exit(EXIT_FAILURE);
   }

#ifndef NDEBUG
   printf("Remote address is: ");
#endif

   char addressBuffer[bufferLen];
   char serviceBuffer[bufferLen];
   getnameinfo(peerAddr->ai_addr, peerAddr->ai_addrlen,
               addressBuffer, sizeof(addressBuffer),
               serviceBuffer, sizeof(serviceBuffer),
               NI_NUMERICHOST);

#ifndef NDEBUG
   printf("%s %s\n", addressBuffer, serviceBuffer);
   printf("Creating socket...\n");
#endif

   SOCKET server = socket(peerAddr->ai_family,
                          peerAddr->ai_socktype,
                          peerAddr->ai_protocol);
   if (!ISVALIDSOCKET(server))
   {
#ifndef NDEBUG
      fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
#endif

      exit(EXIT_FAILURE);
   }

#ifndef NDEBUG
   printf("Connecting...\n");
#endif

   if (connect(server, peerAddr->ai_addr, peerAddr->ai_addrlen))
   {
#ifndef NDEBUG
      fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
#endif

      exit(EXIT_FAILURE);
   }

   freeaddrinfo(peerAddr);

#ifndef NDEBUG
   printf("Connected.\n\n");
#endif

   return server;
}
