CC=gcc

CFLAGS=-c -Wall -g

all: server

server: server.o logging.o
	$(CC) server.o logging.o -o server
server.o: server.c
	$(CC) $(CFLAGS) server.c

logging.o: logging.c
	$(CC) $(CFLAGS) logging.c
clean:
	rm -rf *o server
