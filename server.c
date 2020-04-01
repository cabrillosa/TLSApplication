#include <openssl/ssl.h>
#include <openssl/err.h>

#include "socket_facade.h"
#define BUFFER 1024
int main(){
    int s = newsocket();
    char message[BUFFER]={0};
    struct sockaddr_in addr;
    uint len = sizeof(addr);
    while(1){
        int client = accept(s,(struct sockaddr*)&addr, &len);
        printf("New connection! %d\n", client);
        read(client, message, BUFFER);
        printf("Client Message: %s", message);
        //memset(&message, 0, BUFFER);
    }
}