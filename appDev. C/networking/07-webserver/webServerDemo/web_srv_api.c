#include "web_srv_api.h"

/**
 * @brief Mime types
 */
const static MimeMapT mime_types[MIME_TYPE_LEN] =
    {
        {".css",  "text/css"},
        {".csv",  "text/csv"},
        {".gif",  "image/gif"},
        {".htm",  "text/html"},
        {".html", "text/html"},
        {".ico",  "image/x-icon"},
        {".jpeg", "image/jpeg"},
        {".jpg",  "image/jpeg"},
        {".js",   "application/javascript"},
        {".json", "application/json"},
        {".png",  "image/png"},
        {".pdf",  "application/pdf"},
        {".svg",  "image/svg+xml"},
        {".txt",  "text/plain"}
    };

/**
 * @brief Connected clients
 */
ClientInfoT *clients = NULL;

const char *get_content_type(const char *aPath)
{
   const char *const pathExt = strrchr(aPath, '.');
   const char *contentType = "application/octet-stream";

   if (pathExt != NULL)
   {
      for (int i = 0; i < MIME_TYPE_LEN; i++)
      {
         const MimeMapT mime = mime_types[i];
         if (strcmp(pathExt, mime.extension) == 0)
         {
            contentType = mime.mime_type;
            break;
         }
      }
   }

   return contentType;
}

SOCKET create_socket(const char *aHost, const char *aPort)
{
#ifndef NDEBUG
   printf("%s", "Configuring local address...\n");
#endif

   struct addrinfo hints;
   memset(&hints, 0, sizeof(hints));
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE;

   struct addrinfo *bindAddress;
   getaddrinfo(aHost, aPort, &hints, &bindAddress);

#ifndef NDEBUG
   printf("%s", "Creating socket...\n");
#endif

   const SOCKET socketListen = socket(bindAddress->ai_family,
                                      bindAddress->ai_socktype,
                                      bindAddress->ai_protocol);
   if (!ISVALIDSOCKET(socketListen))
   {
#ifndef NDEBUG
      fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
#endif

      exit(EXIT_FAILURE);
   }

#ifndef NDEBUG
   printf("Binding socket to local address...\n");
#endif

   if (bind(socketListen, bindAddress->ai_addr, bindAddress->ai_addrlen))
   {
#ifndef NDEBUG
      fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
#endif

      exit(EXIT_FAILURE);
   }

   freeaddrinfo(bindAddress);

#ifndef NDEBUG
   printf("Listening...\n");
#endif

   if (listen(socketListen, CONNECTION_THRESHOLD) < 0)
   {
#ifndef NDEBUG
      fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
#endif

      exit(EXIT_FAILURE);
   }

   return socketListen;
}

ClientInfoT *get_client(const SOCKET aClientSocket)
{
   ClientInfoT *clientInfo = clients;

   while (clientInfo != NULL)
   {
      if (clientInfo->socket == aClientSocket)
      {
         break;
      }

      clientInfo = clientInfo->next;
   }

   if (clientInfo != NULL)
   {
      return clientInfo;
   }

   ClientInfoT *newClientInfo = (ClientInfoT *) calloc(1, sizeof(ClientInfoT));
   if (newClientInfo == NULL)
   {
#ifndef NDEBUG
      fprintf(stderr, "Out of memory.\n");
#endif

      exit(EXIT_FAILURE);
   }

   newClientInfo->address_length = sizeof(newClientInfo->address);
   newClientInfo->next = clients;
   clients = newClientInfo;

   return newClientInfo;
}

void drop_client(ClientInfoT *clientInfo)
{
   CLOSESOCKET(clientInfo->socket);

   ClientInfoT **pTopClientInfo = &clients;
   while (*pTopClientInfo != NULL)
   {
      if (*pTopClientInfo == clientInfo)
      {
         *pTopClientInfo = clientInfo->next;
         free(clientInfo);
         return;
      }

      pTopClientInfo = &(*pTopClientInfo)->next;
   }

#ifndef NDEBUG
   fprintf(stderr, "drop_client not found.\n");
#endif

   exit(EXIT_FAILURE);
}

const char *get_client_address(ClientInfoT *aClientInfo)
{
   static char addressBuffer[BUFFER_LEN];
   getnameinfo((struct sockaddr *) &aClientInfo->address,
               aClientInfo->address_length,
               addressBuffer,
               sizeof(addressBuffer),
               0,
               0,
               NI_NUMERICHOST);

   return addressBuffer;
}

fd_set wait_on_clients(const SOCKET aServerSocket)
{
   fd_set reads;
   FD_ZERO(&reads);
   FD_SET(aServerSocket, &reads);
   SOCKET maxSocket = aServerSocket;

   const ClientInfoT *clientInfo = clients;
   while (clientInfo != NULL)
   {
      FD_SET(clientInfo->socket, &reads);
      if (clientInfo->socket > maxSocket)
      {
         maxSocket = clientInfo->socket;
      }

      clientInfo = clientInfo->next;
   }

   if (select(maxSocket + 1, &reads, 0, 0, 0) < 0)
   {
#ifndef NDEBUG
      fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
#endif

      exit(EXIT_FAILURE);
   }

   return reads;
}

void send_400(ClientInfoT *clientInfo)
{
   const char *badRequest =
       "HTTP/1.1 400 Bad Request\r\n"
       "Connection: close\r\n"
       "Content-Length: 11\r\n\r\nBad Request";
   send(clientInfo->socket, badRequest, strlen(badRequest), 0);
   drop_client(clientInfo);
}

void send_404(ClientInfoT *clientInfo)
{
   const char *notFound =
       "HTTP/1.1 404 Not Found\r\n"
       "Connection: close\r\n"
       "Content-Length: 9\r\n\r\nNot Found";
   send(clientInfo->socket, notFound, strlen(notFound), 0);
   drop_client(clientInfo);
}

void serve_resource(ClientInfoT *aClientInfo, const char *aPath)
{
#ifndef NDEBUG
   printf("serve_resource %s %s\n",
          get_client_address(aClientInfo),
          aPath);
#endif

   if (strcmp(aPath, "/") == 0)
   {
      aPath = "/index.html";
   }

   if (strlen(aPath) > MAX_PATH_LEN)
   {
      send_400(aClientInfo);
      return;
   }

   if (strstr(aPath, ".."))
   {
      send_404(aClientInfo);
      return;
   }

   char fullPath[PATH_BUFFER];
   sprintf(fullPath, "public%s", aPath);

#if defined(_WIN32)
   char* pToPath = fullPath;
   while (*pToPath != '\0')
   {
      if (*pToPath == '/')
      {
         *pToPath = '\\';
      }

      ++pToPath;
   }
#endif

   FILE *fpResource = fopen(fullPath, "rb");
   if (!fpResource)
   {
      send_404(aClientInfo);
      return;
   }

   fseek(fpResource, 0L, SEEK_END);
   const size_t contentLen = ftell(fpResource);
   rewind(fpResource);

   const char *contentType = get_content_type(fullPath);
   char buffer[BUFFER_SIZE];

   sprintf(buffer, "HTTP/1.1 200 OK\r\n");
   send(aClientInfo->socket, buffer, strlen(buffer), 0);

   sprintf(buffer, "Connection: close\r\n");
   send(aClientInfo->socket, buffer, strlen(buffer), 0);

   sprintf(buffer, "Content-Length: %zu\r\n", contentLen);
   send(aClientInfo->socket, buffer, strlen(buffer), 0);

   sprintf(buffer, "Content-Type: %s\r\n", contentType);
   send(aClientInfo->socket, buffer, strlen(buffer), 0);

   sprintf(buffer, "\r\n");
   send(aClientInfo->socket, buffer, strlen(buffer), 0);

   int readLen = fread(buffer, 1, BUFFER_SIZE, fpResource);
   while (readLen)
   {
      send(aClientInfo->socket, buffer, readLen, 0);
      readLen = fread(buffer, 1, BUFFER_SIZE, fpResource);
   }

   fclose(fpResource);
   drop_client(aClientInfo);
}
