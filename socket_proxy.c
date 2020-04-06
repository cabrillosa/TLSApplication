#include "socket_proxy.h"

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

int socket_new_server(){
    int sockfd;
    struct sockaddr_in addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0 ){
        perror("Error Creating Socket!\n");
        exit(ERROR_CANNOT_CREATE_SOCKET);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("Error binding to port!\n");
        exit(ERROR_CANNOT_BIND_PORT);
    }
    if(listen(sockfd, 1) < 0){
        perror("Error listening to assigned port!\n");
        exit(ERROR_LISTEN);
    }
    return sockfd;   
}

int socket_new_client(const char *hostname, int port){
    int sockfd;
    struct hostent *host;
    struct sockaddr_in addr;

    if((host = gethostbyname(hostname)) == NULL){
        perror("unable to resolve hostname!\n");
        exit(ERROR_CANNOT_RESOLVE_HOSTNAME);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long *)(host->h_addr);
    if(connect(sockfd,(struct sockaddr *)&addr, sizeof(addr)) != 0){
        close(sockfd);
        perror("Error connecting to server!\n");
        exit(ERROR_CANNOT_CONNECT_SERVER);
    }
    return sockfd;
}

//======================================================
//socket_accept(int socket, struct sockaddr_in addr, uint size)
//params:
//    socket - socket file descriptor
//    addr - structure for holding address family, port, etc
//    size - structure size in memory
//return:
//   sockfd (int)
//=======================================================

int socket_accept(int socket, struct sockaddr_in addr, uint size){
    //TODO: Perform error handling
   return accept(socket, (struct sockaddr *)&addr, &size);
}

//======================================================
//socket_close(int sockfd)
//params:
//    sockfd - socket file descriptor
//return:
//   void
//=======================================================
void socket_close(int sockfd){
    close(sockfd);
}