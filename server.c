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

#define PORT 8080
#define IP_ADDR "127.0.0.1"
#define BUF_SIZE 1024

int main(int argc, char** argv){
	struct sockaddr_in server_addr, client_addr;
	int s_sockfd, c_sockfd, len;
	int pid;
	socklen_t sin_siz;
	unsigned short s_port;
	unsigned int c_port;
	int recv_size, send_size;
	char send_buf[BUF_SIZE], recv_buf[BUF_SIZE];
	//open socket discripter
	if( (s_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("sock error");
		exit(EXIT_FAILURE);
	}
	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	//set server socket config
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons((unsigned short)PORT);
	server_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
	
	//bind socket discriptor and server address config
	if( bind(s_sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr))<0) {
		perror("bind error\n");
		close(s_sockfd);
		exit(EXIT_FAILURE);
	}

	//set server listen
	if( listen(s_sockfd, 4) < 0){
		perror("listen error\n");
		close(s_sockfd);
		exit(EXIT_FAILURE);
	}

	//accept connection
	//fork and copy process into child after connected
	//close parent connection
	//each client connect through c_sockfd
	int *status;
	while(1){
		fprintf(stdout, "waiting connect...\n");
		//while(1){

		if((c_sockfd = accept(s_sockfd, (struct sockaddr *)&client_addr, &sin_siz))<0){
			perror("accept\n");
			close(s_sockfd);
			close(c_sockfd);
			exit(EXIT_FAILURE);
		}
	//	printf("connect from %s: %d\n",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	//	memset(recv_buf, 0, BUF_SIZE);

		pid = fork();
		//child close server socket
		//parent close client socket
		if(pid==0){
			fprintf(stderr, "child: pid=%d\nchild finish\n",pid);
			close(s_sockfd);
			printf("connect from %s: %d\n",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			memset(recv_buf, 0, BUF_SIZE);
			memset(send_buf, 0, BUF_SIZE);

			
			recv_size = recv(c_sockfd, recv_buf, BUF_SIZE, 0);
			while(strncasecmp(recv_buf, "exit\n", 5) != 0){
				//recv_size = recv(c_sockfd, recv_buf, BUF_SIZE, 0);
				if(recv_size == -1){
					fprintf(stderr, "recv error\n");
					perror("recv\n");
					close(c_sockfd);
					exit(EXIT_FAILURE);
				}
				if(recv_size == 0){
					fprintf(stderr, "connection end\n");
					close(c_sockfd);
					break;
				}
				send_size = send(c_sockfd, recv_buf, recv_size, 0);
				if(strcmp(recv_buf, "finish\n") == 0){
				/*		
				recv_buf[len] = '\0';
				printf("<== %s\n", recv_buf);
				send_size = send(c_sockfd, , len, 0);
				*/
					//send_size = send(c_sock, %send_buf, 1, 0);
					if( send_size == -1){
						perror("send error\n");
						close(c_sockfd);
						break;
					}
					fprintf(stderr, "connection finish\n");
					close(c_sockfd);
					break;
				}
				recv_size = recv(c_sockfd, recv_buf, BUF_SIZE, 0);
			}

			fprintf(stderr, "finish while recv send\n");
		}else{
			fprintf(stderr, "parent: pid=%d\n",pid);
			close(c_sockfd);
			//exit(0);
			//fprintf(stderr, "parent: pid=%d\nparent finish",pid);
			/*if((c_sockfd = accept(s_sockfd, (struct sockaddr *)&client_addr, &sin_siz))<0){
				perror("accept\n");
				close(s_sockfd);
				close(c_sockfd);
				exit(EXIT_FAILURE);
			}*/
			wait(status);
			if(WIFEXITED(*status)) {
				printf("Exit: %d\n", WEXITSTATUS(*status));
			}
		}

		/*printf("connect from %s: %d\n",inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		memset(recv_buf, 0, BUF_SIZE);
*/
		/*while(strncasecmp(recv_buf, "exit\n", 5) != 0){
			len = recv(c_sockfd, recv_buf, BUF_SIZE, 0);
			recv_buf[len] = '\0';
			printf("<== %s\n", recv_buf);
			len = send(c_sockfd, recv_buf, len, 0);
		}*/
		//close(c_sockfd);
		//}
	}
	printf("finish::::\n");
	close(s_sockfd);
	return 0;
}
