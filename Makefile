CC = g++
CFLAGS = -g -Wall

all: server client

server: server.cpp
	$(CC) $(CFLAGS) -o $@ $<

client: client.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	-rm -f *.o *~ *core* server client
