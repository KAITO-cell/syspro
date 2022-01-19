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
#include "util.h"



int main(int argc, char** argv){
	////struct sockaddr_in server_addr, client_addr;
	struct sockaddr_in client_addr;
	socket_data server;
	int c_sockfd;
	int pid;
	socklen_t sin_siz;
	int recv_size, send_size;
	char send_buf[BUF_SIZE], recv_buf[BUF_SIZE];
	server = set_server(argv[1]);
	sin_siz = sizeof(struct sockaddr_in);
	memset(recv_buf, 0, BUF_SIZE);
    memset(send_buf, 0, BUF_SIZE);
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
			char name[20];
			pid_t child_pid = getpid();
			fprintf(stderr, "child: pid=%d\n",child_pid);
			//close server socketfd
			close(server.sockfd);
			recv_size = recv(c_sockfd, recv_buf, BUF_SIZE, 0);
			printf("connect from %s: %d[%s]\n",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port),name);
			
			strcpy(name, recv_buf);
			send_size =sprintf(send_buf, "hello [%s]\n",name);
			send_size = send(c_sockfd, send_buf, send_size, 0);
			memset(recv_buf, 0, BUF_SIZE);
		    memset(send_buf, 0, BUF_SIZE);
			while(1){

				fprintf(stderr,"wait for client\n");
				recv_size = recv(c_sockfd, recv_buf, BUF_SIZE, 0);
				
				printf("message from %d[%s]: %s\n",getpid(),name,recv_buf);
				check_recive_size(recv_size,c_sockfd);
				if(strcmp(recv_buf, "game") == 0) {
					start_question(c_sockfd);
				}
				if(strcmp(recv_buf, "exit")==0) break;
				send_size =sprintf(send_buf, "get [%s] from you\n",recv_buf);
				send_size = send(c_sockfd, send_buf, send_size, 0);
				memset(recv_buf, 0, BUF_SIZE);
			    memset(send_buf, 0, BUF_SIZE);
				
			}
			// send_size =sprintf(send_buf, "start question");
        	// send_size =(sockfd,send_buf,send_size, 0);
			
			fprintf(stderr, "finish while recv send\n");
			if(strcmp(recv_buf, "exit")==0){
				//send_size =sprintf(send_buf, "get [%s] from you\n",recv_buf);
				send_size = send(c_sockfd, recv_buf, recv_size, 0);
				close(c_sockfd);
				exit(EXIT_SUCCESS);
			}
			//finish child process
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
	close(c_sockfd);
	close(server.sockfd);
	return 0;
}
