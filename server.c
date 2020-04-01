
#include "socket_facade.h"
#include "openssl_facade.h"
#define BUFFER 1024
int main(){
    int socket;
    SSL_CTX *sslctx;

    openssl_init();
    sslctx = openssl_create_context();
    openssl_configure_context(sslctx);

    socket = newsocket();

    while(1){
        struct sockaddr_in addr;
        uint size = sizeof(addr);
        SSL *myssl;
        char client_message[BUFFER] = {0};
        char server_message[] = "HTTP/1.1 200 OK\r\n\r\n<h1>SD15 Network Team!</h1>\r\n\r\n";

        int clientsocket = socket_accept(socket, addr, size);
        if(clientsocket < 0){
            perror("Error accepting connection! \n");
            exit(ERROR_ACCEPT_CONNECTION);
        }
               
        
        myssl = SSL_new(sslctx);
        SSL_set_fd(myssl, clientsocket);

    

        if(SSL_accept(myssl) <= 0){
            ERR_print_errors_fp(stderr);
        } else {
            SSL_read(myssl, client_message, strlen(client_message));
            printf("Client message: %s\n", client_message);
            SSL_write(myssl, server_message, strlen(server_message));
        }
        SSL_shutdown(myssl);
        SSL_free(myssl);
        close(clientsocket);
    }

    close(socket);
    SSL_CTX_free(sslctx);
    openssl_cleanEVP();
    



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