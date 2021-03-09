#ifndef SELECT_SERVER_NETWORK_UTILS_H
#include <sys/socket.h>

/**
 * Get socket address (IPv4 or IPv6)
 * @param p_socket_address ponter to socket address
 * @return socket address
 */
void *get_in_addr(struct sockaddr* p_socket_address);

#define SELECT_SERVER_NETWORK_UTILS_H

#endif //SELECT_SERVER_NETWORK_UTILS_H
