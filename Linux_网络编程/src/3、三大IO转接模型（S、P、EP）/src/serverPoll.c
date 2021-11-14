#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <errno.h>
#include <ctype.h>
#include "wrap.h"

char *IPSRC = "127.0.0.1";
#define SERV_PORT 8000

#define OPEN_MAX 1024//监听的客户端上限
#define MAXLINE 80//读数据大小

int main(int argc, char *argv[])
{
    int i, maxi, listenfd, connfd, sockfd;
    int nready;   //接收poll返回值, 记录满足监听事件的fd个数
    ssize_t n;

    char buf[MAXLINE], str[INET_ADDRSTRLEN];
    socklen_t clilen;
    struct pollfd client[OPEN_MAX];//poll函数的第一个参数结构体
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    //servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, IPSRC, &(servaddr.sin_addr.s_addr));//自己定义ip
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    Listen(listenfd, 128);
	 //用-1初始化client[]里剩下元素
    for (i = 0; i < OPEN_MAX; i++)
        client[i].fd = -1;   
/*
	struct pollfd {
		int fd; 	   // 文件描述符 
		short events;  //监控的事件 
		short revents; // 监控事件中满足条件返回的事件，操作系统赋值 
	};
*/
    client[0].fd = listenfd;      //要监听的第一个文件描述符 存入client[0]
    client[0].events = POLLIN;    //listenfd监听普通读事件
	
    maxi = 0;  // client[]数组有效元素中最大元素下标，记录有多少个被监听：maxi+1
	

    for (;;) {
		
        nready = poll(client, maxi+1, -1);   //-1：阻塞监听是否有客户端链接请求
		//------------------------------connect require-----------
		//取位图操作
        if (client[0].revents & POLLIN) {       // listenfd有读事件就绪

            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
            printf("received from %s at PORT %d\n",
                    inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
                    ntohs(cliaddr.sin_port));

            for (i = 1; i < OPEN_MAX; i++)
                if (client[i].fd < 0) {
                    client[i].fd = connfd;//找到client[]中空闲的位置,存放connfd
                    break;
                }
		    client[i].events = POLLIN;   //设置刚刚返回的connfd,监控读事件
			
            if (i == OPEN_MAX)                 //达到了最大客户端数
                perr_exit("too many clients");
			
            if (i > maxi)
                maxi = i;      //更新client[]中最大元素下标
            if (--nready <= 0)
                continue;    //没有更多就绪事件时,就直接结束本次循环，回到poll阻塞
        }
		//-------------------------------data deal------------
        for (i = 1; i <= maxi; i++) {    //检测client[] 看是那个数据connfd就绪
            if ((sockfd = client[i].fd) < 0)
                continue;

            if (client[i].revents & POLLIN) {

                if ((n = Read(sockfd, buf, MAXLINE)) < 0) {
                    
                    if (errno == ECONNRESET) { //收到RST标志，连接异常（客户端退出但未关闭连接），需要关闭fd
                        printf("client[%d] aborted connection\n", i);
                        Close(sockfd);
                        client[i].fd = -1;  
                    } else
                        perr_exit("read error");

                } else if (n == 0) {    // 说明客户端了关闭链接 
                    printf("client[%d] closed connection\n", i);
                    Close(sockfd);
                    client[i].fd = -1;
                } else {
                    for (int j = 0; j < n; j++)
                        buf[j] = toupper(buf[j]);
                    Write(sockfd, buf, n);
                }
                if (--nready <= 0)
                    break;
            }
        }
    }
    return 0;
}

