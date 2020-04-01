#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 4433

enum {
    OK = 0,
    ERROR_CANNOT_CREATE_SOCKET = -1,
    ERROR_CANNOT_BIND_PORT = -2,
    ERROR_LISTEN
} RETURN_CODE;


int newsocket();


