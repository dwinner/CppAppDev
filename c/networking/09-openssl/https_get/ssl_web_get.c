//
// Created by ubuntu on 12/27/22.
//

#include "ssl_web_get.h"

void parse_url(char *aUrl, char **aHostname, char **aPort, char **aPath)
{
   printf("URL: %s\n", aUrl);

   char *poPosition = strstr(aUrl, "://");
   char *protocol = 0;
   if (poPosition)
   {
      protocol = aUrl;
      *poPosition = 0;
      poPosition += 3;
   }
   else
   {
      poPosition = aUrl;
   }

   if (protocol && strcmp(protocol, "https") != 0)
   {
      fprintf(stderr,
              "Unknown protocol '%s'. Only 'https' is supported.\n",
              protocol);
      exit(EXIT_FAILURE);
   }

   *aHostname = poPosition;
   while (*poPosition && *poPosition != ':' && *poPosition != '/' && *poPosition != '#')
   {
      ++poPosition;
   }

   *aPort = "443";
   if (*poPosition == ':')
   {
      *poPosition++ = 0;
      *aPort = poPosition;
   }

   while (*poPosition && *poPosition != '/' && *poPosition != '#')
   {
      ++poPosition;
   }

   *aPath = poPosition;
   if (*poPosition == '/')
   {
      *aPath = poPosition + 1;
   }

   *poPosition = 0;

   while (*poPosition && *poPosition != '#')
   {
      ++poPosition;
   }

   if (*poPosition == '#')
   {
      *poPosition = 0;
   }

   printf("hostname: %s\n", *aHostname);
   printf("port: %s\n", *aPort);
   printf("path: %s\n", *aPath);
}

void send_request(SSL *anSsl, char *aHostname, char *aPort, char *aPath)
{
   char buffer[BUFFER_SIZE];

   sprintf(buffer, "GET /%s HTTP/1.1\r\n", aPath);
   sprintf(buffer + strlen(buffer), "Host: %s:%s\r\n", aHostname, aPort);
   sprintf(buffer + strlen(buffer), "Connection: close\r\n");
   sprintf(buffer + strlen(buffer), "User-Agent: honpwc https_get 1.0\r\n");
   sprintf(buffer + strlen(buffer), "\r\n");

   SSL_write(anSsl, buffer, (int) strlen(buffer));
   printf("Sent Headers:\n%s", buffer);
}

SOCKET connect_to_host(char *aHostname, char *aPort)
{
   printf("Configuring remote address...\n");
   struct addrinfo hints;
   memset(&hints, 0, sizeof(hints));
   hints.ai_socktype = SOCK_STREAM;
   struct addrinfo *peerAddr;
   if (getaddrinfo(aHostname, aPort, &hints, &peerAddr))
   {
      fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
      exit(EXIT_FAILURE);
   }

   printf("Remote address is: ");
   char addressBuffer[ADDR_BUFFER];
   char serviceBuffer[ADDR_BUFFER];
   getnameinfo(peerAddr->ai_addr, peerAddr->ai_addrlen,
               addressBuffer, sizeof(addressBuffer),
               serviceBuffer, sizeof(serviceBuffer),
               NI_NUMERICHOST);
   printf("%s %s\n", addressBuffer, serviceBuffer);

   printf("Creating socket...\n");
   SOCKET server = socket(peerAddr->ai_family,
                          peerAddr->ai_socktype,
                          peerAddr->ai_protocol);
   if (!ISVALIDSOCKET(server))
   {
      fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
      exit(EXIT_FAILURE);
   }

   printf("Connecting...\n");
   if (connect(server,
               peerAddr->ai_addr, peerAddr->ai_addrlen))
   {
      fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
      exit(1);
   }

   freeaddrinfo(peerAddr);

   printf("Connected.\n\n");

   return server;
}
