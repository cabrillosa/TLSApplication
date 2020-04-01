
#include "openssl_facade.h"

//======================================================
//void openssl_init() - initializes openssl
//params:
//   none
//return:
//    none
//=======================================================
void openssl_init(){
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
SSL_CTX *openssl_create_context(){
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