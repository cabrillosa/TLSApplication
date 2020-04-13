
#include "socket_proxy.h"
#include "openssl_proxy.h"

#define BUFFER 1024

int main(){
    int socket;
    SSL_CTX *sslctx;

    //initialize and configure context
    openssl_init();
    sslctx = openssl_create_server_context();
    openssl_configure_context(sslctx);

    //create server socket for listening at port 443
    socket = socket_new_server();

    //process all incoming client connection request
    while(1){
        //necessary variable/structure declarations
        struct sockaddr_in addr;
        uint size = sizeof(addr);
        SSL *myssl;
        char client_message[BUFFER] = {0};
        char server_message[] = "HTTP/1.1 200 OK\r\n\r\n<h1>SD15 Network Team!</h1>\r\n\r\n";

        //accept incoming client connection and get client socket
        int clientsocket = socket_accept(socket, addr, size);
        if(clientsocket < 0){
            perror("Error accepting connection! \n");
            return ERROR_ACCEPT_CONNECTION;
        }

        //create new SSL connection
        myssl = openssl_new_connection(sslctx, clientsocket);

        if(myssl == NULL){
            return ERROR_OPENSSL_NEW_CONNECTION;
        }

        //accept new SSL connection
        if(!(openssl_accept_connection(myssl) <= OK)){
            //read client request
            openssl_read(myssl, client_message, BUFFER);
            printf("client request: %s\n", client_message);
            
            //send response to client
            openssl_write(myssl, server_message, strlen(server_message));
        }

        //clean current session and close client socket
        openssl_clean_session(myssl);
        socket_close(clientsocket);
    }

    //terminate server side connection/socket and cleanup OPENSSL memory
    openssl_clean_connection(sslctx);   
    openssl_cleanEVP();
    socket_close(socket);
    



    // int s = newsocket();
    // char message[BUFFER]={0};
    // struct sockaddr_in addr;
    // uint len = sizeof(addr);
    // while(1){
    //     int client = accept(s,(struct sockaddr*)&addr, &len);
    //     printf("New connection! %d\n", client);
    //     read(client, message, BUFFER);
    //     printf("Client Message: %s", message);
    //     //memset(&message, 0, BUFFER);
    // }
}