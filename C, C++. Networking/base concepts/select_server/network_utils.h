#ifndef SELECT_SERVER_NETWORK_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

/**
 * Get socket address (IPv4 or IPv6)
 * @param p_socket_address Ponter to socket address
 * @return Socket address
 */
void *get_in_addr(struct sockaddr *p_socket_address);

/**
 * Set address info components
 * @param addr_info pointer to pointer to address info to be set
 * @param port_num Port number
 */
void set_stream_address(struct addrinfo **addr_info, const char *port_num);

/**
 * Get opened, active server socket descriptor
 * @param addr_info Address info to build from
 * @return Socket desriptor or -1 if it could not bind or create
 */
int get_server_listener(struct addrinfo *addr_info);

#define SELECT_SERVER_NETWORK_UTILS_H

#endif //SELECT_SERVER_NETWORK_UTILS_H
