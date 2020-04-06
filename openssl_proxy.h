#include <openssl/ssl.h>
#include <openssl/err.h>

#include "error.h"

//======================================================
//void openssl_init() - initializes openssl
//params:
//   none
//return:
//    none
//=======================================================
void openssl_init();


//======================================================
//void openssl_cleanEVP() - cleans up used EVPs
//params:
//    none
//return:
//    none
//=======================================================
void openssl_cleanEVP();


//======================================================
//SSL_CTX *openssl_create_context() -  create openssl CTX
//params:
//   
//return:
//    SSL_CTX
//=======================================================
SSL_CTX *openssl_create_server_context();

SSL_CTX *openssl_create_client_context();


//======================================================
//openssl_configure_context(SSL_CTX) - configure ctx
//params:
//    SSL_CTX - pointer to ctx to configure
//return:
//    None
//=======================================================
void openssl_configure_context(SSL_CTX*);

//=============================================================================/
//openssl_new_connection(SSL_CTX* sslctx, int clientsocket)
//    creates a new SSL connection
//params:
//    SSL_CTX - pointer to ssl context
//    clientsocket - for SSL_set_fd() , setting myssl to client file descriptor
//return:
//    SSL* pointer to the newly configured SSL connection
//=============================================================================/
SSL *openssl_new_connection(SSL_CTX*, int);

void openssl_show_certificate(SSL *ssl);


int openssl_client_connect(SSL *ssl);

int openssl_read(SSL* myssl, char* server_message, int len);


//=============================================================================/
//openssl_accept_connection(SSL* myssl)
//    accept a new SSL connection
//params:
//    SSL* - pointer to ssl context
//return:
//    int result - contains the result of SSL_accept() function
//=============================================================================/
int openssl_accept_connection(SSL*);

//=============================================================================/
//openssl_write(SSL* myssl, char* server_message, int len)
//    compose buffer, perform PKES, and send the encrypted data to the client
//params:
//    SSL* - pointer to ssl context
//    server_message - pointer to char buffer of server reply
//    len - length of char buffer
//return: void
//=============================================================================/
void openssl_write(SSL*, char*, int);

//=============================================================================/
//oopenssl_clean_session(SSL* myssl)
//    clean the current TLS session
//params:
//    SSL* - pointer to ssl contextf char buffer
//return: void
//=============================================================================/
void openssl_clean_session(SSL*);

//=============================================================================/
//openssl_clean_connection(SSL_CTX* myssl)
//    close the current TLS connection
//params:
//    SSL_CTX* -pointer to SSL_CTX structure
//return: void
//=============================================================================/
void openssl_clean_connection(SSL_CTX*);