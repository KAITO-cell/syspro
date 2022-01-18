#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> //socket()
#include <sys/socket.h> //socket() bind() accept() listen()
#include <arpa/inet.h> //struct sockaddr
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "server.h"
socket_data set_server(){
	socket_data server;
	if( (server.sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket error");
		close(server.sockfd);
		exit(EXIT_FAILURE);
	}
	memset(&server.addr, 0, sizeof(struct sockaddr_in));
	server.addr.sin_family = PF_INET;
	server.addr.sin_port = htons((unsigned short)PORT);
	server.addr.sin_addr.s_addr = inet_addr(IP_ADDR);
	if( bind(server.sockfd, (const struct sockaddr *)&server, sizeof(server))<0) {
		perror("bind error\n");
		close(server.sockfd);
		exit(EXIT_FAILURE);
	}

	//set server listen
	if( listen(server.sockfd, 4) < 0){
		perror("listen error\n");
		close(server.sockfd);
		exit(EXIT_FAILURE);
	}
	return server;
}

void check_recive_size(int recv_size,int c_sockfd){
    if(recv_size == -1){
			perror("recv_size = -1");
			close(c_sockfd);
			exit(EXIT_FAILURE);
	}
	if(recv_size == 0){
        	perror("recv_size = 0");
			close(c_sockfd);
			exit(EXIT_FAILURE);
	}
}