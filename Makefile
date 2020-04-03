CC=gcc
CFLAGS=-g -Wall
INCLUDEPATH=-I. -I/home/pi/Desktop/WFH/openssl-1.1.1d_install/include
LIBPATH=-L/home/pi/Desktop/WFH/openssl-1.1.1d_install/lib -L.
LIBS=-lssl -lcrypto

server.o:socket_proxy.h socket_proxy.c server.c openssl_proxy.h openssl_proxy.c
	$(CC) $(CFLAGS) $^ -o $@ $(INCLUDEPATH) $(LIBS) $(LIBPATH)

clean:
	rm -rf *.o