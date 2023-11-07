#ifndef WEB_GET_WEB_GET_H
#define WEB_GET_WEB_GET_H

#include "network.h"

#define TIMEOUT 5.0

/**
 * Parses URL
 * @param url Url to be parsed
 * @param hostname Host name as output
 * @param port Port as Output
 * @param path Path as Output
 */
void parse_url(char *url, char **hostname, char **port, char **path);

/**
 * Sends request
 * @param socket Socket desc.
 * @param hostname Host name
 * @param port Port
 * @param path Path
 */
void send_request(SOCKET socket, char *hostname, char *port, char *path);

/**
 * Connect to host
 * @param hostname Host name
 * @param port Port
 * @return Socket desc.
 */
SOCKET connect_to_host(char *hostname, char *port);

#endif //WEB_GET_WEB_GET_H
