#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> //socket()
#include <sys/socket.h> //socket() bind() accept() listen()
#include <sys/wait.h>
#include <arpa/inet.h> //struct sockaddr
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "calc.h"
#include "server.h"



int main(int argc, char** argv){
	////struct sockaddr_in server_addr, client_addr;
	struct sockaddr_in client_addr;
	socket_data server;
	int c_sockfd;
	int pid;
	socklen_t sin_siz;
	int recv_size, send_size;
	char send_buf[BUF_SIZE], recv_buf[BUF_SIZE];
	server = set_server();
			
	//accept connection
	//fork and copy process into child after connected
	//close parent connection
	//each client connect through c_sockfd
	int *status;
	while(1){
		fprintf(stdout, "waiting connect...\n");
		if((c_sockfd = accept(server.sockfd, (struct sockaddr *)&client_addr, &sin_siz))<0){
			perror("accept\n");
			close(server.sockfd);
			close(c_sockfd);
			exit(EXIT_FAILURE);
		}
		pid = fork();
		//child close server socket
		//parent close client socket
		if(pid==0){
			pid_t child_pid = getpid();
			fprintf(stderr, "child: pid=%d\nchild finish\n",child_;id);
			//close server socketfd
			close(server.sockfd);
			printf("connect from %s: %d\n",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			memset(recv_buf, 0, BUF_SIZE);
			memset(send_buf, 0, BUF_SIZE);
			
			Question question;
			Data d;
			d.correct_label = 1;
			char q_statement[1024];
			int q_size;
			q_size=sprintf( q_statement, "%d + %d = ?\n",question.left,question.right);
			//fprintf(stderr,"%s\n",q_statement);
			//recv_size = recv(c_sockfd, recv_buf, BUF_SIZE, 0);
			//printf("server first: recv message: %s\n",recv_buf);
			int state = 0;
			while(strcmp(recv_buf, "finish") != 0){
				fprintf(stderr,"wait for client\n");
				//switch(state){
					//case 0:
						recv_size = recv(c_sockfd, recv_buf, BUF_SIZE, 0);
						printf("server in while: recv message from %d: %s\n",getpid(),recv_buf);
						check_recive_size(recv_size,c_sockfd);
						send_size = send(c_sockfd, q_statement, q_size, 0);
						/*if(strcmp(recv_buf, "finish") == 0){
							if( send_size == -1){
								perror("send error\n");
								close(c_sockfd);
								break;
							}
							fprintf(stderr, "connection finish\n");
							close(c_sockfd);
							break;
						}*/
					//	break;
					//}
					//case 1:
				//recv_size = recv(c_sockfd, recv_buf, BUF_SIZE, 0);
			}
			fprintf(stderr, "finish while recv send\n");
			close(c_sockfd);//finish child process
		}else{//parent process
			fprintf(stderr, "parent: pid=%d\n",pid);
			close(c_sockfd);
			//wait(status);
			//if(WIFEXITED(*status)) {
			//	printf("Exit: %d\n", WEXITSTATUS(*status));
			//}
		}

	}
	printf("finish::::\n");
	close(server.sockfd);
	return 0;
}
