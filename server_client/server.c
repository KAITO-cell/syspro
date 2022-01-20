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
	socket_data server;
	socket_data client;
	socklen_t sin_siz;
	int recv_size, send_size;
	char send_buf[BUF_SIZE], recv_buf[BUF_SIZE];
	server = set_server(argv);
	sin_siz = sizeof(struct sockaddr_in);
	memset(recv_buf, 0, BUF_SIZE);
    memset(send_buf, 0, BUF_SIZE);
    if (argc != 3) {
        printf("Usage: ./prog host port¥n");
        exit(1);
    }
	//accept connection
	//fork and copy process into child after connected
	//close parent connection
	//each client connect through c_sockfd
	int *status;
	while(1){
		fprintf(stdout, "waiting connect...\n");
		if((client.sockfd = accept(server.sockfd, (struct sockaddr *)&client.addr, &sin_siz))<0){
			perror("accept\n");
			close(server.sockfd);
			close(client.sockfd);
			exit(EXIT_FAILURE);
		}
		int pid; 
		pid = fork();
		//child close server socket
		//parent close client socket
		if(pid==0){
			char name[20];
			pid_t child_pid = getpid();
			fprintf(stderr, "child: pid=%d\n",child_pid);
			//close server socketfd
			close(server.sockfd);
			recv_size = recv(client.sockfd, recv_buf, BUF_SIZE, 0);
			strcpy(name, recv_buf);
			printf("connect from %s: %d[%s]\n",inet_ntoa(client.addr.sin_addr), ntohs(client.addr.sin_port),name);
			send_size =sprintf(send_buf, "hello [%s]\n",name);
			send_size = send(client.sockfd, send_buf, send_size, 0);
			check_send_size(send_size,client.sockfd);
			memset(recv_buf, 0, BUF_SIZE);
		    memset(send_buf, 0, BUF_SIZE);
			
			while(1){

				//fprintf(stderr,"wait for client\n");
				
				char* c_time = (char*)malloc(sizeof(char)*20);
				current_time(c_time);
				recv_size = recv(client.sockfd, recv_buf, BUF_SIZE, 0);
				check_recive_size(recv_size,client.sockfd);
				//printf("from %d[%s]: %s\n",getpid(),name,recv_buf);
				printf("%s [%s]: %s\n",c_time,name,recv_buf);


				if(strcmp(recv_buf, "game") == 0) {
					//start_question(client.sockfd);
						fprintf(stdout,"the answer from client is %s\n",recv_buf);
						send_size =sprintf(send_buf, "game start");
            			send_size =(client.sockfd,send_buf,send_size, 0);
						check_send_size(send_size,client.sockfd);
						fprintf(stdout,"the answer from client is %s\n",send_buf);
						memset(recv_buf, 0, BUF_SIZE);
		   				memset(send_buf, 0, BUF_SIZE);
						recv_size = recv(client.sockfd, recv_buf, BUF_SIZE, 0);//ready
						fprintf(stdout,"the answer from client is %s\n",recv_buf);
						check_recive_size(recv_size,client.sockfd);
						
					// 	User user;
					//     user.data.q_number = 0;
        			// 	user.data.correct_label = 1;
					// while(1){
					// 	if(user.data.correct_label == 1)
					// 		user.question = make_question();
					// 		memset(recv_buf, 0, BUF_SIZE);
					// 	// memset(send_buf, 0, BUF_SIZE);
	    			// 	send_size =sprintf(send_buf, "calculate expression:%d + %d = ?", user.question.right, user.question.left);
            		// 	send_size =(client.sockfd,send_buf,send_size, 0);

					// 	//答えもらう
					// 	recv_size = recv(client.sockfd, recv_buf, BUF_SIZE, 0);
				    //     fprintf(stdout,"the answer from client is %s\n",recv_buf);
					// 	check_recive_size(recv_size,client.sockfd);
	    			// 	int response = atoi(recv_buf);
	    			// 	user.data = eval_answer(response,user);

					// }

				}

				if(strcmp(recv_buf, "goodbye")==0){
					printf("%s is logout\n",name);
					close(client.sockfd);
					exit(EXIT_SUCCESS);
				}
				send_size =sprintf(send_buf, "get [%s] from you\n",recv_buf);
				send_size = send(client.sockfd, send_buf, send_size, 0);
				memset(recv_buf, 0, BUF_SIZE);
			    memset(send_buf, 0, BUF_SIZE);	
			}
        	// send_size =(sockfd,send_buf,send_size, 0);
			//fprintf(stderr, "finish while communicate\n");
		}else{//parent process
			fprintf(stderr, "parent: pid=%d\n",pid);
			close(client.sockfd);
			//wait(status);
			//if(WIFEXITED(*status)) {
			//	printf("Exit: %d\n", WEXITSTATUS(*status));
			//}
		}
	}
	printf("finish::::\n");
	close(client.sockfd);
	close(server.sockfd);
	return 0;
}
