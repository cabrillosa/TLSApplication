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
SSL_CTX *openssl_create_context();


//======================================================
//openssl_configure_context(SSL_CTX) - configure ctx
//params:
//    SSL_CTX - pointer to ctx to configure
//return:
//    None
//=======================================================