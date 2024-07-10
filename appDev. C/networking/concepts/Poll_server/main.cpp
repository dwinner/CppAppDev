/**
 * pollserver.c -- a cheezy multiperson chat server
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

/**
 * \brief Port we're listening on
 */
constexpr int port = 9034;

// Get sockaddr, IPv4 or IPv6:
void* get_in_addr(struct sockaddr* socket_addr)
{
   if (socket_addr->sa_family == AF_INET)
   {
      return &reinterpret_cast<sockaddr_in*>(socket_addr)->sin_addr;
   }

   return &reinterpret_cast<sockaddr_in6*>(socket_addr)->sin6_addr;
}

// Return a listening socket
int get_listener_socket(void)
{
   int listener_socket = 0; // Listening socket descriptor
   int yes = 1; // For setsockopt() SO_REUSEADDR, below
   int ret_val;

   struct addrinfo hints{}, *addr_info, *p_lnk_idx;

   // Get us a socket and bind it
   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE;
   if ((ret_val = getaddrinfo(nullptr, port, &hints, &addr_info)) != 0)
   {
      fprintf(stderr, "selectserver: %s\n", gai_strerror(ret_val));
      exit(1);
   }

   for (p_lnk_idx = addr_info; p_lnk_idx != nullptr; p_lnk_idx = p_lnk_idx->ai_next)
   {
      listener_socket = socket(p_lnk_idx->ai_family, p_lnk_idx->ai_socktype, p_lnk_idx->ai_protocol);
      if (listener_socket < 0)
      {
         continue;
      }

      // Lose the pesky "address already in use" error message
      setsockopt(listener_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

      if (bind(listener_socket, p_lnk_idx->ai_addr, p_lnk_idx->ai_addrlen) < 0)
      {
         close(listener_socket);
         continue;
      }

      break;
   }

   // If we got here, it means we didn't get bound
   if (p_lnk_idx == nullptr)
   {
      return -1;
   }

   freeaddrinfo(addr_info); // All done with this

   // Listen
   if (listen(listener_socket, 10) == -1)
   {
      return -1;
   }

   return listener_socket;
}

// Add a new file descriptor to the set
void add_to_pfds(struct pollfd* p_fds[], const int new_fd, int* fd_count, int* fd_size)
{
   // If we don't have room, add more space in the pfds array
   if (*fd_count == *fd_size)
   {
      *fd_size *= 2; // Double it
      *p_fds = static_cast<pollfd*>(realloc(*p_fds, sizeof **p_fds * *fd_size));
   }

   (*p_fds)[*fd_count].fd = new_fd;
   (*p_fds)[*fd_count].events = POLLIN; // Check ready-to-read

   (*fd_count)++;
}

// Remove an index from the set
void del_from_pfds(struct pollfd pfds[], const int idx, int* fd_count)
{
   // Copy the one from the end over this one
   pfds[idx] = pfds[*fd_count - 1];

   (*fd_count)--;
}

// Main
int main()
{
   struct sockaddr_storage remoteaddr{}; // Client address
   socklen_t addrlen;

   char buf[256]; // Buffer for client data

   char remote_ip[INET6_ADDRSTRLEN];

   // Start off with room for 5 connections
   // (We'll realloc as necessary)
   int fd_count;
   int fd_size = 5;
   struct pollfd* pfds = static_cast<struct pollfd*>(malloc(sizeof *pfds * fd_size));

   // Set up and get a listening socket
   const int listener = get_listener_socket();

   if (listener == -1)
   {
      fprintf(stderr, "error getting listening socket\n");
      exit(1);
   }

   // Add the listener to set
   pfds[0].fd = listener;
   pfds[0].events = POLLIN; // Report ready to read on incoming connection

   fd_count = 1; // For the listener

   // Main loop
   for (;;)
   {
      const int poll_count = poll(pfds, fd_count, -1);

      if (poll_count == -1)
      {
         perror("poll");
         exit(1);
      }

      // Run through the existing connections looking for data to read
      for (int i = 0; i < fd_count; i++)
      {
         // Check if someone's ready to read
         if (pfds[i].revents & POLLIN)
         {
            // We got one!!
            if (pfds[i].fd == listener)
            {
               // If listener is ready to read, handle new connection
               addrlen = sizeof remoteaddr;

               // Newly accept()ed socket descriptor
               const int new_fd = accept(listener,
                                         reinterpret_cast<sockaddr*>(&remoteaddr),
                                         &addrlen);

               if (new_fd == -1)
               {
                  perror("accept");
               }
               else
               {
                  add_to_pfds(&pfds, new_fd, &fd_count, &fd_size);
                  printf("pollserver: new connection from %s on socket %d\n",
                         inet_ntop(remoteaddr.ss_family,
                                   get_in_addr(reinterpret_cast<sockaddr*>(&remoteaddr)),
                                   remote_ip, INET6_ADDRSTRLEN),
                         new_fd);
               }
            }
            else
            {
               // If not the listener, we're just a regular client
               const int nbytes = recv(pfds[i].fd, buf, sizeof buf, 0);
               const int sender_fd = pfds[i].fd;

               if (nbytes <= 0)
               {
                  // Got error or connection closed by client
                  if (nbytes == 0)
                  {
                     // Connection closed
                     printf("pollserver: socket %d hung up\n", sender_fd);
                  }
                  else
                  {
                     perror("recv");
                  }

                  close(pfds[i].fd); // Bye!
                  del_from_pfds(pfds, i, &fd_count);
               }
               else
               {
                  // We got some good data from a client
                  for (int j = 0; j < fd_count; j++)
                  {
                     // Send to everyone!
                     const int dest_fd = pfds[j].fd;

                     // Except the listener and ourselves
                     if (dest_fd != listener && dest_fd != sender_fd)
                     {
                        if (send(dest_fd, buf, nbytes, 0) == -1)
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

   //return 0;
}
