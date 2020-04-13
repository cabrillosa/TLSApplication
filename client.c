#include "openssl_proxy.h"
#include "socket_proxy.h"

#define BUFFER 1024

int main(){

    int serversocket;
    SSL *myssl;
    char server_reply_buffer[BUFFER] = {0};
    char *clientreq_buffer = "GET / HTTP/1.1\r\n\r\n";
    SSL_CTX *sslctx;



    openssl_init();
    sslctx = openssl_create_client_context();

    serversocket = socket_new_client("localhost",443); 

    myssl = openssl_new_connection(sslctx, serversocket);

    if(openssl_client_connect(myssl) != -1){
        //show server certificate information
        openssl_show_certificate(myssl);

        //send HTTP GET request to the server
        openssl_write(myssl, clientreq_buffer, strlen(clientreq_buffer));  

        //get server response
        openssl_read(myssl, server_reply_buffer, BUFFER);
        
        printf("Server reply: %s\n", server_reply_buffer);

    }
    openssl_clean_session(myssl);
    openssl_clean_connection(sslctx);  
    socket_close(serversocket);

    return 0;
}