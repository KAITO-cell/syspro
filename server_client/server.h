#ifndef _SERVER_H__
#define _SERVER_H__

typedef struct {
	struct sockaddr_in addr;
	int sockfd;
} socket_data;

socket_data set_server();

#endif

