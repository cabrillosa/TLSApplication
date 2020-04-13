Basic TLS Server using openssl1.1.1d

How to run the application:
1. clone this repository to your linux device:
    git clone https://github.com/cabrillosa/TLSApplication.git
2. Download openssl1.1.1d at openssl.org
3. Install openssl1.1.1d, follow the steps on how to install at their installation guide. Take note on where you set your openssldir.
4. cd to TLSApplication
5. Edit Makefile
    INCLUDEPATH=-I. -I[PATH TO OPENSSL INCLUDEDIR]
    LIBPATH=-L[PATH TO OPENSSL LIBDIR]-L.
6. chmod 777 build.sh
7. ./build.sh --> produces build.log server client
8. sudo ./server --> run server side first.
9. In another terminal, run ./client --> run client side after server side.
10. Client console should display "<h2>SD15 Network Team</h2>".

Alernative:
Open any web browser and type https://127.0.0.1 in address bar, "SD15 Network Team" will be displayed.

Thanks!
