#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> //socket()
#include <sys/socket.h> //socket() bind() accept() listen()
#include <arpa/inet.h> //struct sockaddr
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "util.h"
#include "calc.h"

socket_data set_server(char** argv){
	socket_data server;
	int port;
	if( (server.sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket error");
		close(server.sockfd);
		exit(EXIT_FAILURE);
	}
	memset(&server.addr, 0, sizeof(struct sockaddr_in));
	server.addr.sin_family = PF_INET;
	port = strtol(argv[2], NULL, 10);
	server.addr.sin_port = htons(port);
	server.addr.sin_addr.s_addr = inet_addr(argv[1]);
	//net_aton(argv[1], &serv.sin_addr);
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

socket_data set_client(char** argv){
	socket_data client;
	int port;
	if( (client.sockfd = socket(PF_INET, SOCK_STREAM, 0))< 0 ){
        perror("socket error\n");
        exit(EXIT_FAILURE);
    }
    memset(&client.addr, 0, sizeof(struct sockaddr_in));
    client.addr.sin_family = PF_INET;
    port = strtol(argv[2], NULL, 10);
    client.addr.sin_port = htons((unsigned short)port);
    client.addr.sin_addr.s_addr = inet_addr(argv[1]);
    fprintf(stdout,"Start connect...\n");
    if (connect(client.sockfd, (struct sockaddr*)&client.addr, sizeof(struct sockaddr_in)) < 0) {
        perror("connect error\n");
        close(client.sockfd);
        exit(EXIT_FAILURE);
    }
	return client;
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

void check_send_size(int send_size,int c_sockfd){
    if(send_size == -1){
			perror("send_size = -1");
			close(c_sockfd);
			exit(EXIT_FAILURE);
	}
	if(send_size == 0){
        	perror("send_size = 0");
			close(c_sockfd);
			exit(EXIT_FAILURE);
	}
}

void start_question(int sockfd){
		// fprintf(stdout,"get [start] from client \n");
		// printf("start question\n");
        int send_size,recv_size;
        char recv_buf[BUF_SIZE], send_buf[BUF_SIZE];
        User user;
        user.data.q_number = 0;
        user.data.correct_label = 1;
		memset(recv_buf, 0, BUF_SIZE);
		memset(send_buf, 0, BUF_SIZE);
		send_size = sprintf(send_buf, "game start");
		send_size = send(sockfd, send_buf, send_size, 0);
		
		recv_size = recv(sockfd, recv_buf, BUF_SIZE, 0);//ready
		printf("in question,from%d :%s\n",getpid(),recv_buf);
        while(user.data.q_number < 10){
	    	int response;
	    	//char[1024] statement;
            user.question = make_question();
			memset(recv_buf, 0, BUF_SIZE);
			memset(send_buf, 0, BUF_SIZE);
	    	send_size =sprintf(send_buf, "calculate expression:%d + %d = ?", user.question.right, user.question.left);
            send_size =(sockfd,send_buf,send_size, 0);
			printf("send[%s]\n",send_buf);
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

void current_time(char* c_time){
	time_t t = time(NULL);
	struct tm *local= localtime(&t);
	int year, month, day, hour, min, sec;
	year = local->tm_year+1900;
	month = local->tm_mon+1;
	day = local->tm_mday;
	hour = local->tm_hour;
	min = local->tm_min;
	sec = local->tm_sec;
	sprintf(c_time,"%04d/%02d/%02d %02d:%02d:%02d",year,month,day,hour,min,sec);
}























