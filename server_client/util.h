#ifndef _UTIL_H__
#define _UTIL_H__
#define PORT 8080
#define IP_ADDR "127.0.0.1"
#define BUF_SIZE 1024

typedef struct {
	struct sockaddr_in addr;
	int sockfd;
} socket_data;

socket_data set_server(char** argv);
socket_data set_client(char** argv);
void check_recive_size(int recv_size,int c_sockfd);
void check_send_size(int send_size,int c_sockfd);
void start_question(int sockfd);
void current_time(char* c_time);
#endif
