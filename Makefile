TARGET = server client
CC = /usr/bin/gcc
CFLAGS = -g -DDEBUG
OBJS = server.o client.o

all: $(TARGET)

server: server.o
	$(CC) -o $@ $^

client: client.o
	$(CC) -o $@ $^

clean: 
	rm -rf $(TARGET) *~.o *.o
