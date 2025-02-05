CC = gcc
CFLAGS = -I.
DEPS = constants.h
OBJ = server.o client.o constants.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: server.o constants.o
	$(CC) -o server server.o constants.o

client: client.o constants.o
	$(CC) -o client client.o constants.o

all: server client
.PHONY: clean

clean:
	rm -f *.o server client