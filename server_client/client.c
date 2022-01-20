#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "util.h"
#include "calc.h"
// #define PORT 8080
// #define S_ADDR "127.0.0.1"
// #define BUF_SIZE 1024

int main(int argc,char** argv){
    struct sockaddr_in addr;
    socket_data client;
    char send_buf[BUF_SIZE], recv_buf[BUF_SIZE];
    int send_size, recv_size;
    
    //open filediscriptor for socket
    if (argc != 3) {
        printf("Usage: ./prog host port¥n");
        exit(1);
    }
    client = set_client(argv);

    printf("Finish connect! clietsockfd=%d\n",client.sockfd);
    char name[20];
    memset(name, 0, 20);
    memset(recv_buf, 0, BUF_SIZE);
	memset(send_buf, 0, BUF_SIZE);
    printf("enter you name:");
    //scanf("%s",name);
    fgets(name, 20, stdin);
    name[strlen(name)-1] = '\0'; 

    send_size = send(client.sockfd, name,strlen(name),0);
    check_send_size(send_size,client.sockfd);
    recv_size = recv(client.sockfd, recv_buf,BUF_SIZE,0);
    check_recive_size(recv_size,client.sockfd);
    printf("%s\n",recv_buf);
    /* 接続済のソケットでデータのやり取り */
    //transfer(clietsockfd);
    while(1){
    	memset(recv_buf, 0, BUF_SIZE);
		memset(send_buf, 0, BUF_SIZE);
        //get string sending to server
        printf("Input Message...\n");
        fgets(send_buf, BUF_SIZE, stdin);
        send_buf[strlen(send_buf)-1] = '\0'; 
        send_size = send(client.sockfd, send_buf,strlen(send_buf),0);
        check_send_size(send_size,client.sockfd);
        //printf("send [%s]\n",send_buf);
        if(send_size == -1){
            perror("send error");
            close(client.sockfd);
            break;
        }
        //recieve response from server
        //printf("wait recieve\n");
        recv_size = recv(client.sockfd, recv_buf,BUF_SIZE,0);
        check_recive_size(recv_size,client.sockfd);
        printf("from server:%s\n",recv_buf);
        if(strcmp(recv_buf, "goodbye")==0) {
            break;
        }
        
        if(strcmp(recv_buf, "game start") == 0){
            //recv_size = recv(client.sockfd, recv_buf,BUF_SIZE,0);
            //check_recive_size(recv_size,client.sockfd);
            printf("[%s] from server in fame start\n",recv_buf);
            send_size = sprintf(send_buf,"ready");
            send_size = send(client.sockfd, send_buf,strlen(send_buf),0);
            check_send_size(send_size, client.sockfd);
            recv_size = recv(client.sockfd, recv_buf,BUF_SIZE,0);//問題のはず
            printf("after send ready\n");
            int i =0;
            while(strcmp(recv_buf, "question finish.") != 0){
                //get question from server
                fprintf(stderr,"in while recv message: %s\n",recv_buf);
                if(i!=0){
                    recv_size = recv(client.sockfd, recv_buf,BUF_SIZE,0);
                }
                i++;
                fprintf(stderr,"from server:%s\n",recv_buf);
                scanf("%s", send_buf);
                send_size = send(client.sockfd, send_buf,strlen(send_buf),0);//回答
            }

        }

    }
    //start question
    //fprintf(stderr,"recv message: %s\nfinish connection\n",recv_buf);
    
	//break;
    /* ソケット通信をクローズ *///socket discriptor close
    close(client.sockfd);
    return 0;
}
