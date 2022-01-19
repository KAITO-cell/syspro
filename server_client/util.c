#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> //socket()
#include <sys/socket.h> //socket() bind() accept() listen()
#include <arpa/inet.h> //struct sockaddr
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "util.h"
#include "calc.h"
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

void start_question(int sockfd){
        int send_size,recv_size;
        char recv_buf[BUF_SIZE], send_buf[BUF_SIZE];
        User user;
        user.data.q_number = 0;
        user.data.correct_label = 1;
	   	send_size =sprintf(send_buf, "start question\n");
        send_size =(sockfd,send_buf,send_size, 0);
        while(user.data.q_number < 10){
	    	int response;
	    	//char[1024] statement;
            user.question = make_question();
	    	send_size =sprintf(send_buf, "%d + %d = ?\n",user.question.right,user.question.left);
            send_size =(sockfd,send_buf,send_size, 0);
            recv_size = recv(sockfd, recv_buf, BUF_SIZE, 0);
            fprintf(stdout,"the answer from client is %s\n",recv_buf);
			check_recive_size(recv_size,sockfd);
	    	response = atoi(recv_buf);
	    	user.data = eval_answer(response,user);
        }
	send_size =sprintf(send_buf, "question finish.\n faultcount:%d\n",user.data.fault_count);
        send_size =(sockfd,send_buf,send_size, 0);
	//return user
}



