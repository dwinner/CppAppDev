#include "ssl_network.h"

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

   SSL_library_init();
   OpenSSL_add_all_algorithms();
   SSL_load_error_strings();

   SSL_CTX *ctx = SSL_CTX_new(TLS_server_method());
   if (!ctx)
   {
      fprintf(stderr, "SSL_CTX_new() failed.\n");
      return EXIT_FAILURE;
   }

   if (!SSL_CTX_use_certificate_file(ctx, "cert.pem", SSL_FILETYPE_PEM)
       || !SSL_CTX_use_PrivateKey_file(ctx, "key.pem", SSL_FILETYPE_PEM))
   {
      fprintf(stderr, "SSL_CTX_use_certificate_file() failed.\n");
      ERR_print_errors_fp(stderr);
      return EXIT_FAILURE;
   }

   printf("Configuring local address...\n");
   struct addrinfo hints;
   memset(&hints, 0, sizeof(hints));
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE;

   struct addrinfo *bindAddr;
   getaddrinfo(0, "8080", &hints, &bindAddr);

   printf("Creating socket...\n");
   SOCKET socketListen = socket(bindAddr->ai_family,
                                bindAddr->ai_socktype,
                                bindAddr->ai_protocol);
   if (!ISVALIDSOCKET(socketListen))
   {
      fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
      return EXIT_FAILURE;
   }

   printf("Binding socket to local address...\n");
   if (bind(socketListen,
            bindAddr->ai_addr, bindAddr->ai_addrlen))
   {
      fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
      return EXIT_FAILURE;
   }

   freeaddrinfo(bindAddr);

   printf("Listening...\n");
   if (listen(socketListen, 10) < 0)
   {
      fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
      return EXIT_FAILURE;
   }

   while (1)
   {
      printf("Waiting for connection...\n");
      struct sockaddr_storage clientAddress;
      socklen_t clientLen = sizeof(clientAddress);
      SOCKET socketClient = accept(socketListen,
                                   (struct sockaddr *) &clientAddress, &clientLen);
      if (!ISVALIDSOCKET(socketClient))
      {
         fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
         return EXIT_FAILURE;
      }

      printf("Client is connected... ");
      char addressBuffer[100];
      getnameinfo((struct sockaddr *) &clientAddress,
                  clientLen, addressBuffer, sizeof(addressBuffer), 0, 0,
                  NI_NUMERICHOST);
      printf("%s\n", addressBuffer);

      SSL *ssl = SSL_new(ctx);
      if (!ssl)
      {
         fprintf(stderr, "SSL_new() failed.\n");
         return EXIT_FAILURE;
      }

      SSL_set_fd(ssl, socketClient);
      if (SSL_accept(ssl) <= 0)
      {
         fprintf(stderr, "SSL_accept() failed.\n");
         ERR_print_errors_fp(stderr);

         SSL_shutdown(ssl);
         CLOSESOCKET(socketClient);
         SSL_free(ssl);

         continue;
      }

      printf("SSL connection using %s\n", SSL_get_cipher(ssl));

      printf("Reading request...\n");
      char request[1024];
      int bytesReceived = SSL_read(ssl, request, 1024);
      printf("Received %d bytes.\n", bytesReceived);
      printf("Sending response...\n");
      const char *response =
         "HTTP/1.1 200 OK\r\n"
         "Connection: close\r\n"
         "Content-Type: text/plain\r\n\r\n"
         "Local time is: ";
      int responseLen = (int) strlen(response);
      int bytesSent = SSL_write(ssl, response, responseLen);
      printf("Sent %d of %d bytes.\n", bytesSent, responseLen);

      time_t timer;
      time(&timer);
      char *timeMsg = ctime(&timer);
      bytesSent = SSL_write(ssl, timeMsg, (int) strlen(timeMsg));
      printf("Sent %d of %d bytes.\n", bytesSent, (int) strlen(timeMsg));

      printf("Closing connection...\n");
      SSL_shutdown(ssl);
      CLOSESOCKET(socketClient);
      SSL_free(ssl);
   }

   printf("Closing listening socket...\n");
   CLOSESOCKET(socketListen);
   SSL_CTX_free(ctx);

#if defined(_WIN32)
   WSACleanup();
#endif

   printf("Finished.\n");

   return EXIT_SUCCESS;
}