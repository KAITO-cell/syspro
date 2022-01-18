TARGET = server
CC = /usr/bin/gcc
CFLAGS = -g -DDEBUG
SRCS = server.c client.c calc.c util.c 
OBJS = server.o client.o calc.o util.o

all: $(TARGET)

.c.o:
	$(CC) -c $< -o $@

server:	server.o calc.o util.o
	$(CC) -o $@ $^

client: client.o
	$(CC) -o $@ $^

clean: 
	rm -rf $(TARGET) *~.o *.o
