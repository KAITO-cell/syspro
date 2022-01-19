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
    int sockfd;
    struct sockaddr_in addr;
    char send_buf[BUF_SIZE], recv_buf[BUF_SIZE];
    int send_size, recv_size;
    //open filediscriptor for socket
    
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0 ){
        perror("socket error\n");
        exit(EXIT_FAILURE);
    }


    /* サーバーのIPアドレスとポートの情報を設定 */
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = PF_INET;
    addr.sin_port = htons((unsigned short)PORT);
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    /* サーバーに接続要求送信 */
    fprintf(stdout,"Start connect...\n");
    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0) {
        perror("connect error\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Finish connect! sockfd=%d\n",sockfd);
    char name[20];
    printf("enter you name:");
    scanf("%s",name);
  	memset(recv_buf, 0, BUF_SIZE);
	memset(send_buf, 0, BUF_SIZE);
    send_size = send(sockfd, name,strlen(name),0);//
    recv_size = recv(sockfd, recv_buf,BUF_SIZE,0);
    printf("%s\n",recv_buf);
    /* 接続済のソケットでデータのやり取り */
    //transfer(sockfd);
    while(1){
    	memset(recv_buf, 0, BUF_SIZE);
		memset(send_buf, 0, BUF_SIZE);
        //get string sending to server
        printf("Input Message...\n");
        
        scanf("%s", send_buf);

        //send message
        //send_size = sprintf(send_buf,"%s: %s",name,message);
        send_size = send(sockfd, send_buf,strlen(send_buf),0);//
        //printf("send [%s]\n",send_buf);
        if(send_size == -1){
            perror("send error");
            close(sockfd);
            break;
        }
        //recieve response from server
        //printf("wait recieve\n");
        recv_size = recv(sockfd, recv_buf,BUF_SIZE,0);
        check_recive_size(recv_size,sockfd);
        printf("from server:%s\n",recv_buf);
        if(strcmp(recv_buf, "goodbye")==0) {
            //send exit response
            //send(sockfd,send_buf,send_size,0);
            //get goodby message
            recv(sockfd,recv_buf,recv_size,0);
            printf("%s\n",recv_buf);
            break;
        }
        if(strcmp(recv_buf, "game start") == 0){
            printf("[%s] from server\n",recv_buf);
            send_size = sprintf(send_buf,"ready");
            send_size = send(sockfd, send_buf,strlen(send_buf),0);
            printf("after send ready\n");
            while(strcmp(recv_buf, "question finish.") != 0){
                //get question from server
                fprintf(stderr,"in while recv message: %s\n",recv_buf);
                recv_size = recv(sockfd, recv_buf,BUF_SIZE,0);
                fprintf(stderr,"from server:%s\n",recv_buf);
                scanf("%s", send_buf);
                send_size = send(sockfd, send_buf,strlen(send_buf),0);//回答
            }

        }

    }
    //start question
    fprintf(stderr,"recv message: %s\nfinish connection\n",recv_buf);
    
	//break;
    /* ソケット通信をクローズ *///socket discriptor close
    close(sockfd);
    return 0;
}
