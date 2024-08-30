//
// Created by ubuntu on 12/27/22.
//

#include "ssl_web_srv.h"

client_info_t *clients = NULL;

const char *get_content_type(const char *aPath)
{
   const char *lastDot = strrchr(aPath, '.');
   if (lastDot)
   {
      if (strcmp(lastDot, ".css") == 0)
      {
         return "text/css";
      }

      if (strcmp(lastDot, ".csv") == 0)
      {
         return "text/csv";
      }

      if (strcmp(lastDot, ".gif") == 0)
      {
         return "image/gif";
      }

      if (strcmp(lastDot, ".htm") == 0)
      {
         return "text/html";
      }

      if (strcmp(lastDot, ".html") == 0)
      {
         return "text/html";
      }

      if (strcmp(lastDot, ".ico") == 0)
      {
         return "image/x-icon";
      }

      if (strcmp(lastDot, ".jpeg") == 0)
      {
         return "image/jpeg";
      }

      if (strcmp(lastDot, ".jpg") == 0)
      {
         return "image/jpeg";
      }

      if (strcmp(lastDot, ".js") == 0)
      {
         return "application/javascript";
      }

      if (strcmp(lastDot, ".json") == 0)
      {
         return "application/json";
      }

      if (strcmp(lastDot, ".png") == 0)
      {
         return "image/png";
      }

      if (strcmp(lastDot, ".pdf") == 0)
      {
         return "application/pdf";
      }

      if (strcmp(lastDot, ".svg") == 0)
      {
         return "image/svg+xml";
      }

      if (strcmp(lastDot, ".txt") == 0)
      {
         return "text/plain";
      }
   }

   return "application/octet-stream";
}

SOCKET create_socket(const char *aHost, const char *aPort)
{
   printf("Configuring local address...\n");
   struct addrinfo hints;
   memset(&hints, 0, sizeof(hints));
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE;

   struct addrinfo *bindAddress;
   getaddrinfo(aHost, aPort, &hints, &bindAddress);

   printf("Creating socket...\n");
   SOCKET socketListen = socket(bindAddress->ai_family,
                                bindAddress->ai_socktype,
                                bindAddress->ai_protocol);
   if (!ISVALIDSOCKET(socketListen))
   {
      fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
      exit(EXIT_FAILURE);
   }

   printf("Binding socket to local address...\n");
   if (bind(socketListen,
            bindAddress->ai_addr, bindAddress->ai_addrlen))
   {
      fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
      exit(EXIT_FAILURE);
   }

   freeaddrinfo(bindAddress);

   printf("Listening...\n");
   if (listen(socketListen, 10) < 0)
   {
      fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
      exit(EXIT_FAILURE);
   }

   return socketListen;
}

client_info_t *get_client(SOCKET aSocket)
{
   client_info_t *client = clients;

   while (client != NULL)
   {
      if (client->socket == aSocket)
      {
         break;
      }

      client = client->next;
   }

   if (client != NULL)
   {
      return client;
   }

   client_info_t *newClient = (client_info_t *) calloc(1, sizeof(client_info_t));
   if (newClient == NULL)
   {
      fprintf(stderr, "Out of memory.\n");
      exit(EXIT_FAILURE);
   }

   newClient->address_length = sizeof(newClient->address);
   newClient->next = clients;
   clients = newClient;

   return newClient;
}

void drop_client(client_info_t *aClient)
{
   SSL_shutdown(aClient->ssl);
   CLOSESOCKET(aClient->socket);
   SSL_free(aClient->ssl);

   client_info_t **poClient = &clients;
   while (*poClient != NULL)
   {
      if (*poClient == aClient)
      {
         *poClient = aClient->next;
         free(aClient);
         return;
      }

      poClient = &(*poClient)->next;
   }

   exit(EXIT_FAILURE);
}

const char *get_client_address(client_info_t *aClient)
{
   static char addressBuffer[100];
   getnameinfo((struct sockaddr *) &aClient->address,
               aClient->address_length,
               addressBuffer, sizeof(addressBuffer), 0, 0,
               NI_NUMERICHOST);

   return addressBuffer;
}

fd_set wait_on_clients(SOCKET aServerSocket)
{
   fd_set reads;
   FD_ZERO(&reads);
   FD_SET(aServerSocket, &reads);
   SOCKET maxSocketFd = aServerSocket;

   struct client_info *currentClient = clients;
   while (currentClient != NULL)
   {
      FD_SET(currentClient->socket, &reads);
      if (currentClient->socket > maxSocketFd)
      {
         maxSocketFd = currentClient->socket;
      }

      currentClient = currentClient->next;
   }

   if (select(maxSocketFd + 1, &reads, 0, 0, 0) < 0)
   {
      fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
      exit(EXIT_FAILURE);
   }

   return reads;
}

void send_400(client_info_t *aClient)
{
   const char *badRequest = "HTTP/1.1 400 Bad Request\r\n"
                            "Connection: close\r\n"
                            "Content-Length: 11\r\n\r\nBad Request";
   SSL_write(aClient->ssl, badRequest, (int) strlen(badRequest));
   drop_client(aClient);
}

void send_404(client_info_t *aClient)
{
   const char *notFound = "HTTP/1.1 404 Not Found\r\n"
                          "Connection: close\r\n"
                          "Content-Length: 9\r\n\r\nNot Found";
   SSL_write(aClient->ssl, notFound, (int) strlen(notFound));
   drop_client(aClient);
}

void serve_resource(client_info_t *aClient, const char *aPath)
{
   printf("serve_resource %s %s\n", get_client_address(aClient), aPath);

   if (strcmp(aPath, "/") == 0)
   {
      aPath = "/index.html";
   }

   if (strlen(aPath) > 100)
   {
      send_400(aClient);
      return;
   }

   if (strstr(aPath, ".."))
   {
      send_404(aClient);
      return;
   }

   char fullPath[128];
   sprintf(fullPath, "./public%s", aPath);

#if defined(_WIN32)
   char *p = fullPath;
   while (*p)
   {
      if (*p == '/')
      {
         *p = '\\';
      }

      ++p;
   }
#endif

   FILE *fileResource = fopen(fullPath, "rb");
   if (fileResource == NULL)
   {
      send_404(aClient);
      return;
   }

   fseek(fileResource, 0L, SEEK_END);
   size_t fileSize = ftell(fileResource);
   rewind(fileResource);

   const char *contentType = get_content_type(fullPath);
   char buffer[BSIZE];

   sprintf(buffer, "HTTP/1.1 200 OK\r\n");
   SSL_write(aClient->ssl, buffer, (int) strlen(buffer));

   sprintf(buffer, "Connection: close\r\n");
   SSL_write(aClient->ssl, buffer, (int) strlen(buffer));

   sprintf(buffer, "Content-Length: %zu\r\n", fileSize);
   SSL_write(aClient->ssl, buffer, (int) strlen(buffer));

   sprintf(buffer, "Content-Type: %s\r\n", contentType);
   SSL_write(aClient->ssl, buffer, (int) strlen(buffer));

   sprintf(buffer, "\r\n");
   SSL_write(aClient->ssl, buffer, (int) strlen(buffer));

   size_t readCount = fread(buffer, 1, BSIZE, fileResource);
   while (readCount > 0)
   {
      SSL_write(aClient->ssl, buffer, readCount);
      readCount = fread(buffer, 1, BSIZE, fileResource);
   }

   fclose(fileResource);
   drop_client(aClient);
}
