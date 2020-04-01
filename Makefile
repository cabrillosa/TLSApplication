CC=gcc
CFLAGS=-g -Wall
INCLUDEPATH=-I. -I/home/pi/Desktop/WFH/openssl-1.1.1d_install/include
LIBPATH=-L/home/pi/Desktop/WFH/openssl-1.1.1d_install/lib -L.
LIBS=-lssl -lcrypto

server.o:socket_facade.h socket_facade.c server.c openssl_facade.h openssl_facade.c
	$(CC) $(CFLAGS) $^ -o $@ $(INCLUDEPATH) $(LIBS) $(LIBPATH)

clean:
	rm -rf *.o