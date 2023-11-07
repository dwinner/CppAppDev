/**
 * Cheezy multiperson char server
 */

#if defined(_WIN32)
#error This program does not support Windows
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "network_utils.h"

/**
 * Port we're listening on
 */
#define PORT "9034"

/**
 * Maximum connections count
 */
#define MAX_CONNECTIONS_COUNT 10

int main()
{
   fd_set master;    // master file descriptor list
   fd_set read_fds;  // temp file descriptor list for select()
   int fd_max;       // maximum file descriptor list for select()

   int listener;     // listening socket descriptor
   int new_fd;       // newly accepted socket descriptor
   struct sockaddr_storage remote_addr;   // client address
   socklen_t addr_len;

   char buffer_data[256];  // buffer for client data
   int bytes_number;

   char remote_ip[INET6_ADDRSTRLEN];

   // clear the master and temp sets
   FD_ZERO(&master);
   FD_ZERO(&read_fds);

   // get us a socket and bind it
   struct addrinfo *addr_info;
   set_stream_address(&addr_info, PORT);
   listener = get_server_listener(addr_info);
   if (listener == -1)
   {
      fprintf(stderr, "selectserver: failed to bind\n");
      exit(2);
   }

   freeaddrinfo(addr_info);   // all done with this

   // listen
   if (listen(listener, MAX_CONNECTIONS_COUNT) == -1)
   {
      perror("listen");
      exit(3);
   }

   // add the listener to the master set
   FD_SET(listener, &master);

   // keep track of the biggest file descriptor
   fd_max = listener;  // so far, it's this one

   // main loop
   for (;;)
   {
      read_fds = master;  // copy it
      if (select(fd_max + 1, &read_fds, NULL, NULL, NULL) == -1)
      {
         perror("select");
         exit(4);
      }

      // run through the existing connections looking for data to read
      for (int i = 0; i <= fd_max; i++)
      {
         // we got one!!
         if (FD_ISSET(i, &read_fds))
         {
            if (i == listener)
            {
               // handle new connections
               addr_len = sizeof remote_addr;
               new_fd = accept(listener, (struct sockaddr *) &remote_addr, &addr_len);

               if (new_fd == -1)
               {
                  perror("accept");
               }
               else
               {
                  FD_SET(new_fd, &master); // add to master set

                  // keep track the max
                  if (new_fd > fd_max)
                  {
                     fd_max = new_fd;
                  }

                  printf("select_server: new connection from %s on socket %d\n",
                         inet_ntop(remote_addr.ss_family,
                                   get_in_addr((struct sockaddr *) &remote_addr),
                                   remote_ip,
                                   INET6_ADDRSTRLEN),
                         new_fd);
               }
            }
            else
            {
               // handle data from a client
               if ((bytes_number = recv(i, buffer_data, sizeof buffer_data, 0)) <= 0)
               {
                  // got error or connection closed by client
                  if (bytes_number == 0)
                  {
                     // connection closed
                     printf("select_server: socket %d hung up\n", i);
                  }
                  else
                  {
                     perror("recv");
                  }

                  close(i);   // bye!
                  FD_CLR(i, &master);  // remove from master set
               }
               else
               {
                  // we got some data from a client
                  for (int j = 0; j <= fd_max; j++)
                  {
                     // send to everyone!
                     if (FD_ISSET(j, &master))
                     {
                        // except the listener and ourselves
                        if (j != listener && j != i)
                        {
                           if (send(j, buffer_data, bytes_number, 0) == -1)
                           {
                              perror("send");
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

   //return 0;
}
