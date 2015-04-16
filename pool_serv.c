#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>

#include "my_pool.c"

#define BUFFER_SIZE 4096
#define MAX 10

int sock_pool(int listen_port);

mysql_pool my_pool[MAX];

int main(int argc, char** argv) {

    int i;
    
    
    //init the mysql pool
    for(i=0; i<MAX; i++)
    {
        my_pool[i].used = 0;
    }

    sock_pool(8888);
    return 0;
}

int sock_pool(int listen_port) {
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[BUFFER_SIZE+1];
    int n;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(listen_port);

    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        close(listenfd);
        return -1;
    }

    if (listen(listenfd, 2048) == -1) {
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        close(listenfd);
        return -1;
    }


    //for client info
    struct sockaddr_in cliaddr;
    socklen_t clilen;



    printf("-----waiting for client's request-----\n");
    while (1) {
        // if ((connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) == -1) {
        if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) == -1) {
            printf("accept socket error: %s(errno: %d)\n", strerror(errno), errno);
            close(listenfd);
            return -1;
        }
        else
        {
            printf("client IP %s\n",inet_ntoa(cliaddr.sin_addr));
        }
        
        memset(&buff, 0, sizeof(buff));
        recv(connfd, buff, BUFFER_SIZE, 0);
        
        //the buff of recv is SQL query
        printf("recv SQL is:    %s\n", buff);
        handle_pool(my_pool, buff, MAX);
        
        // char resp[] = "HTTP/1.0 200 OK\r\n\r\n<html>this is real server!</html>";
        char resp[] = "success call!";
        send(connfd, resp, strlen(resp), 0);
        close(connfd);
    }

    close(listenfd);
    return 0;
}





