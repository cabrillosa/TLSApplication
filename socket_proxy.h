#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "error.h"

#define PORT 443



//======================================================
//newsocket(int port)
//params:
//    PORT - Port number to use when creating new socket
//return:
//   socket file descriptor on success
//    ERROR_CANNOT_CREATE_SOCKET
//    ERROR_CANNOT_BIND_PORT
//    ERROR_LISTEN
//    NULL
//=======================================================

int newsocket();

//======================================================
//socket_accept(int socket, struct sockaddr_in addr, uint size)
//params:
//    socket - socket file descriptor
//    addr - structure for holding address family, port, etc
//    size - structure size in memory
//return:
//   sockfd (int)
//=======================================================
int socket_accept(int, struct sockaddr_in, uint);

//======================================================
//socket_close(int sockfd)
//params:
//    sockfd - socket file descriptor
//return:
//   void
//=======================================================
void socket_close(int sockfd);


