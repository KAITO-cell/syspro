#ifndef _SERVER_H__
#define _SERVER_H__
#define PORT 8080
#define IP_ADDR "127.0.0.1"
#define BUF_SIZE 1024

typedef struct {
	struct sockaddr_in addr;
	int sockfd;
} socket_data;

socket_data set_server();
void check_recive_size(int recv_size,int c_sockfd);
#endif

