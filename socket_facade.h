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

int socket_accept(int, struct sockaddr_in, uint);


