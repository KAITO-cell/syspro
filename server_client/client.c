#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define PORT 8080
#define S_ADDR "127.0.0.1"
#define BUF_SIZE 1024

int main(void){
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
    addr.sin_family = AF_INET;
    addr.sin_port = htons((unsigned short)PORT);
    addr.sin_addr.s_addr = inet_addr(S_ADDR);

    /* サーバーに接続要求送信 */
    fprintf(stdout,"Start connect...\n");
    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0) {
        perror("connect error\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Finish connect! sockfd=%d\n",sockfd);

    /* 接続済のソケットでデータのやり取り */
    //transfer(sockfd);
    while(1){

        //get string sending to server
        printf("Input Message...\n");
        scanf("%s", send_buf);

        //send message
        

        if((send_size = send(sockfd, send_buf,strlen(send_buf)+1,0)) == -1){
            perror("send error");
            break;
        }
        //recieve response from server
       
        if(( recv_size = recv(sockfd, &recv_buf,1,0))==-1){
            printf("recv error\n");
            break;
        }else if(recv_size == 0){
            printf("connection ended\n");
            break;
        } else {
		printf("recv message: %s\n",recv_buf);

	}

        //finish send message if response is 0
        if(recv_size==0){
            printf("Finish connection");
            break;
        }
    }

    /* ソケット通信をクローズ *///socket discriptor close
    close(sockfd);

    return 0;
}
