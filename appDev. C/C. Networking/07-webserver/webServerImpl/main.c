#include "network.h"

const char *get_content_type(const char *path)
{
   const char *last_dot = strrchr(path, '.');
   if (last_dot)
   {
      if (strcmp(last_dot, ".css") == 0)
      {
         return "text/css";
      }

      if (strcmp(last_dot, ".csv") == 0)
      {
         return "text/csv";
      }

      if (strcmp(last_dot, ".gif") == 0)
      {
         return "image/gif";
      }

      if (strcmp(last_dot, ".htm") == 0)
      {
         return "text/html";
      }

      if (strcmp(last_dot, ".html") == 0)
      {
         return "text/html";
      }

      if (strcmp(last_dot, ".ico") == 0)
      {
         return "image/x-icon";
      }

      if (strcmp(last_dot, ".jpeg") == 0)
      {
         return "image/jpeg";
      }

      if (strcmp(last_dot, ".jpg") == 0)
      {
         return "image/jpeg";
      }

      if (strcmp(last_dot, ".js") == 0)
      {
         return "application/javascript";
      }

      if (strcmp(last_dot, ".json") == 0)
      {
         return "application/json";
      }

      if (strcmp(last_dot, ".png") == 0)
      {
         return "image/png";
      }

      if (strcmp(last_dot, ".pdf") == 0)
      {
         return "application/pdf";
      }

      if (strcmp(last_dot, ".svg") == 0)
      {
         return "image/svg+xml";
      }

      if (strcmp(last_dot, ".txt") == 0)
      {
         return "text/plain";
      }
   }

   return "application/octet-stream";
}

SOCKET create_socket(const char *host, const char *port)
{
   printf("Configuring local address...\n");
   struct addrinfo hints;
   memset(&hints, 0, sizeof(hints));
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE;

   struct addrinfo *bind_address;
   getaddrinfo(host, port, &hints, &bind_address);

   printf("Creating socket...\n");
   SOCKET socket_listen;
   socket_listen = socket(bind_address->ai_family,
                          bind_address->ai_socktype,
                          bind_address->ai_protocol);
   if (!ISVALIDSOCKET(socket_listen))
   {
      fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
      exit(1);
   }

   printf("Binding socket to local address...\n");
   if (bind(socket_listen,
            bind_address->ai_addr,
            bind_address->ai_addrlen))
   {
      fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
      exit(1);
   }

   freeaddrinfo(bind_address);

   printf("Listening...\n");
   if (listen(socket_listen, 10) < 0)
   {
      fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
      exit(1);
   }

   return socket_listen;
}

#define MAX_REQUEST_SIZE 2047

struct client_info
{
   socklen_t address_length;
   struct sockaddr_storage address;
   char address_buffer[128];
   SOCKET socket;
   char request[MAX_REQUEST_SIZE + 1];
   int received;
   struct client_info *next;
};

struct client_info *get_client(struct client_info **client_list, SOCKET aSocket)
{
   struct client_info *client = *client_list;
   while (client)
   {
      if (client->socket == aSocket)
      {
         break;
      }

      client = client->next;
   }

   if (client)
   {
      return client;
   }

   struct client_info *newClient = (struct client_info *)calloc(1, sizeof(struct client_info));
   if (!newClient)
   {
      fprintf(stderr, "Out of memory.\n");
      exit(1);
   }

   newClient->address_length = sizeof(newClient->address);
   newClient->next = *client_list;
   *client_list = newClient;

   return newClient;
}

void drop_client(struct client_info **client_list,
                 struct client_info *client)
{
   CLOSESOCKET(client->socket);
   struct client_info **pToPclient = client_list;

   while (*pToPclient)
   {
      if (*pToPclient == client)
      {
         *pToPclient = client->next;
         free(client);
         return;
      }

      pToPclient = &(*pToPclient)->next;
   }

   fprintf(stderr, "drop_client not found.\n");
   exit(1);
}

const char *get_client_address(struct client_info *client)
{
   getnameinfo((struct sockaddr *)&client->address,
               client->address_length,
               client->address_buffer, sizeof(client->address_buffer), 0, 0,
               NI_NUMERICHOST);
   return client->address_buffer;
}

fd_set wait_on_clients(struct client_info **client_list, SOCKET server)
{
   fd_set reads;
   FD_ZERO(&reads);
   FD_SET(server, &reads);
   SOCKET max_socket = server;

   struct client_info *currentClient = *client_list;
   while (currentClient)
   {
      FD_SET(currentClient->socket, &reads);
      if (currentClient->socket > max_socket)
      {
         max_socket = currentClient->socket;
      }

      currentClient = currentClient->next;
   }

   if (select(max_socket + 1, &reads, 0, 0, 0) < 0)
   {
      fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
      exit(1);
   }

   return reads;
}

void send_400(struct client_info **client_list,
              struct client_info *client)
{
   const char *c400 = "HTTP/1.1 400 Bad Request\r\n"
                      "Connection: close\r\n"
                      "Content-Length: 11\r\n\r\nBad Request";
   send(client->socket, c400, strlen(c400), 0);
   drop_client(client_list, client);
}

void send_404(struct client_info **client_list,
              struct client_info *client)
{
   const char *c404 = "HTTP/1.1 404 Not Found\r\n"
                      "Connection: close\r\n"
                      "Content-Length: 9\r\n\r\nNot Found";
   send(client->socket, c404, strlen(c404), 0);
   drop_client(client_list, client);
}

void serve_resource(struct client_info **client_list,
                    struct client_info *client, const char *path)
{

   printf("serve_resource %s %s\n", get_client_address(client), path);

   if (strcmp(path, "/") == 0)
   {
      path = "/index.html";
   }

   if (strlen(path) > 100)
   {
      send_400(client_list, client);
      return;
   }

   if (strstr(path, ".."))
   {
      send_404(client_list, client);
      return;
   }

   char full_path[128];
   sprintf(full_path, "public%s", path);

#if defined(_WIN32)
   char *pToPath = full_path;
   while (*pToPath)
   {
      if (*pToPath == '/')
      {
         *pToPath = '\\';
      }

      ++pToPath;
   }
#endif

   FILE *fp = fopen(full_path, "rb");

   if (!fp)
   {
      send_404(client_list, client);
      return;
   }

   fseek(fp, 0L, SEEK_END);
   size_t cl = ftell(fp);
   rewind(fp);

   const char *ct = get_content_type(full_path);

#define BSIZE 1024
   char buffer[BSIZE];

   sprintf(buffer, "HTTP/1.1 200 OK\r\n");
   send(client->socket, buffer, strlen(buffer), 0);

   sprintf(buffer, "Connection: close\r\n");
   send(client->socket, buffer, strlen(buffer), 0);

   sprintf(buffer, "Content-Length: %u\r\n", cl);
   send(client->socket, buffer, strlen(buffer), 0);

   sprintf(buffer, "Content-Type: %s\r\n", ct);
   send(client->socket, buffer, strlen(buffer), 0);

   sprintf(buffer, "\r\n");
   send(client->socket, buffer, strlen(buffer), 0);

   int readCnt = fread(buffer, 1, BSIZE, fp);
   while (readCnt)
   {
      send(client->socket, buffer, readCnt, 0);
      readCnt = fread(buffer, 1, BSIZE, fp);
   }

   fclose(fp);
   drop_client(client_list, client);
}

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

   SOCKET server = create_socket(0, "8080");
   struct client_info *client_list = 0;

   while (1)
   {
      fd_set reads;
      reads = wait_on_clients(&client_list, server);
      if (FD_ISSET(server, &reads))
      {
         struct client_info *client = get_client(&client_list, -1);
         client->socket = accept(server,
                                 (struct sockaddr *)&(client->address),
                                 &(client->address_length));
         if (!ISVALIDSOCKET(client->socket))
         {
            fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
         }

         printf("New connection from %s.\n", get_client_address(client));
      }

      struct client_info *client = client_list;
      while (client)
      {
         struct client_info *next = client->next;
         if (FD_ISSET(client->socket, &reads))
         {
            if (MAX_REQUEST_SIZE == client->received)
            {
               send_400(&client_list, client);
               client = next;
               continue;
            }

            int r = recv(client->socket,
                         client->request + client->received,
                         MAX_REQUEST_SIZE - client->received, 0);

            if (r < 1)
            {
               printf("Unexpected disconnect from %s.\n",
                      get_client_address(client));
               drop_client(&client_list, client);
            }
            else
            {
               client->received += r;
               client->request[client->received] = 0;

               char *q = strstr(client->request, "\r\n\r\n");
               if (q)
               {
                  *q = 0;
                  if (strncmp("GET /", client->request, 5))
                  {
                     send_400(&client_list, client);
                  }
                  else
                  {
                     char *path = client->request + 4;
                     char *end_path = strstr(path, " ");
                     if (!end_path)
                     {
                        send_400(&client_list, client);
                     }
                     else
                     {
                        *end_path = 0;
                        serve_resource(&client_list, client, path);
                     }
                  }
               }
            }
         }

         client = next;
      }

   }

   printf("\nClosing socket...\n");
   CLOSESOCKET(server);

#if defined(_WIN32)
   WSACleanup();
#endif

   printf("Finished.\n");
   return 0;
}
