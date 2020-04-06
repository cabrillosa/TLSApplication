
#include "openssl_proxy.h"

//======================================================
//void openssl_init() - initializes openssl
//params:
//   none
//return:
//    none
//=======================================================
void openssl_init(){

    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

}


//======================================================
//void openssl_cleanEVP() - cleans up used EVPs
//params:
//    none
//return:
//    none
//=======================================================
void openssl_cleanEVP(){
    EVP_cleanup();
}


//======================================================
//SSL_CTX *openssl_create_context() -  create openssl CTX
//params:
//   
//return:
//    SSL_CTX
//=======================================================
SSL_CTX *openssl_create_server_context(){
    const SSL_METHOD *meth;
    SSL_CTX *ctx;

    meth = SSLv23_server_method();
    
    ctx = SSL_CTX_new(meth);

    if(!ctx){
        perror("unable to create new context!\n");
        ERR_print_errors_fp(stderr);
        exit(ERROR_OPENSSL_CREATE_CTX);
    }
    return ctx;
}

SSL_CTX *openssl_create_client_context(){
    const SSL_METHOD *meth;
    SSL_CTX *ctx;

    meth = SSLv23_client_method();
    
    ctx = SSL_CTX_new(meth);

    if(!ctx){
        perror("unable to create new context!\n");
        ERR_print_errors_fp(stderr);
        exit(ERROR_OPENSSL_CREATE_CTX);
    }
    return ctx;
}


//======================================================
//openssl_configure_context(SSL_CTX) - configure ctx
//params:
//    SSL_CTX - pointer to ctx to configure
//return:
//    None
//=======================================================
void openssl_configure_context(SSL_CTX *ctx){

    //set certificate 
    if(SSL_CTX_use_certificate_file(ctx,"cert.pem", SSL_FILETYPE_PEM) <= 0){
        ERR_print_errors_fp(stderr);
        exit(ERROR_OPENSSL_SET_CERT);
    }

    //set private key
    if(SSL_CTX_use_PrivateKey_file(ctx, "key.pem", SSL_FILETYPE_PEM) <= 0){
        ERR_print_errors_fp(stderr);
        exit(ERROR_OPENSSL_SET_PRIVATEKEY);
    }
}

//=============================================================================/
//openssl_new_connection(SSL_CTX* sslctx, int clientsocket)
//    creates a new SSL connection
//params:
//    SSL_CTX - pointer to ssl context
//    clientsocket - for SSL_set_fd() , setting myssl to client file descriptor
//return:
//    SSL* pointer to the newly configured SSL connection
//=============================================================================/
SSL *openssl_new_connection(SSL_CTX* sslctx, int clientsocket){
    SSL *myssl = SSL_new(sslctx);
    if(!myssl){
        perror("Error setting new TLS Connection!\n");
        ERR_print_errors_fp(stderr);
        return NULL;
    }
    
    SSL_set_fd(myssl, clientsocket);
    return myssl;
    
}

//=============================================================================/
//openssl_accept_connection(SSL* myssl)
//    accept a new SSL connection
//params:
//    SSL* - pointer to ssl context
//return:
//    int result - contains the result of SSL_accept() function
//=============================================================================/
int openssl_accept_connection(SSL* myssl){
    int result = SSL_accept(myssl);
    if(result <= OK){
        ERR_print_errors_fp(stderr);
    }
    return result;
}

//========================
void openssl_show_certificate(SSL *ssl){
    X509 *cert;
    char *part;

    //get server certificate
    cert = SSL_get_peer_certificate(ssl);

    if(cert != NULL){
        printf("Server side Certificate information:\n");
        part = X509_NAME_oneline(X509_get_subject_name(cert),0,0);
        printf("SUbj: %s\n", part);
          part = X509_NAME_oneline(X509_get_issuer_name(cert),0,0);
        printf("CA: %s\n", part);
        free(part);
        X509_free(cert);
    } else {
        printf("No Certificate issued!\n");
    }
}


//================================
int openssl_client_connect(SSL *ssl){
    int result = SSL_connect(ssl);
    if(result == -1){
        ERR_print_errors_fp(stderr);
    }
    return result;
}



//=============================================================================/
//openssl_write(SSL* myssl, char* server_message, int len)
//    compose buffer, perform PKES, and send the encrypted data to the client
//params:
//    SSL* - pointer to ssl context
//    server_message - pointer to char buffer of server reply
//    len - length of char buffer
//return: void
//=============================================================================/
void openssl_write(SSL* myssl, char* server_message, int len){
    SSL_write(myssl, server_message, len);
}

int openssl_read(SSL* myssl, char* server_message, int len){
    return SSL_read(myssl, server_message, len);
}

//=============================================================================/
//oopenssl_clean_session(SSL* myssl)
//    clean the current TLS session
//params:
//    SSL* - pointer to ssl contextf char buffer
//return: void
//=============================================================================/
void openssl_clean_session(SSL* myssl){
    SSL_shutdown(myssl);
    SSL_free(myssl);
}

//=============================================================================/
//openssl_clean_connection(SSL_CTX* myssl)
//    close the current TLS connection
//params:
//    SSL_CTX* -pointer to SSL_CTX structure
//return: void
//=============================================================================/
void openssl_clean_connection(SSL_CTX* sslctx){
    SSL_CTX_free(sslctx);
}

 