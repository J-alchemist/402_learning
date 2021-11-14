#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <ctype.h>
#include "wrap.h"

#define OPEN_MAX 5000
#define MAXLINE 8192

#define SERV_PORT 8000
char *IPSRC = "127.0.0.1";


int main(int argc, char *argv[])
{
    int i, listenfd, connfd, sockfd;
    int  n, num = 0;
    ssize_t nready, efd, res;	//efd根节点
    char buf[MAXLINE], str[INET_ADDRSTRLEN];
    socklen_t clilen;

    struct sockaddr_in cliaddr, servaddr;
    struct epoll_event epevts, ep[OPEN_MAX];       //epevts: epoll_ctl参数  ep[] : epoll_wait参数

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));      //端口复用

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    Listen(listenfd, 128);

    efd = epoll_create(OPEN_MAX);       //创建epoll模型, efd指向红黑树根节点
    if (efd == -1)
        perr_exit("epoll_create error");

    epevts.events = EPOLLIN; 	      //指定listenfd的监听时间为"读"
	epevts.data.fd = listenfd;     
    res = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &epevts);    //将listenfd添加到efd树根的二叉树上
    if (res == -1)
        perr_exit("epoll_ctl error");

    for ( ; ; ) {
        //监听根节点efd，并传出ep
        nready = epoll_wait(efd, ep, OPEN_MAX, -1); 
        if (nready == -1)
            perr_exit("epoll_wait error");

        for (i = 0; i < nready; i++) {
            if (!(ep[i].events & EPOLLIN))      //如果不是"读"事件, 继续循环
                continue;

            if (ep[i].data.fd == listenfd) {    //如果是lfd事件---------链接请求        
                clilen = sizeof(cliaddr);
                connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);    //接受链接

                printf("received from %s at PORT %d\n", 
                        inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), 
                        ntohs(cliaddr.sin_port));
                printf("cfd %d---client %d\n", connfd, ++num);

                epevts.events = EPOLLIN; 
				epevts.data.fd = connfd;
                res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &epevts);//添加叶子
                if (res == -1)
                    perr_exit("epoll_ctl error");

            } else {                                //不是lfd------------数据请求
                sockfd = ep[i].data.fd;
                n = Read(sockfd, buf, MAXLINE);

                if (n == 0) {                       //读到0,说明客户端关闭链接
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);  //将该文件描述符从红黑树摘除
                    if (res == -1)
                        perr_exit("epoll_ctl error");
                    Close(sockfd);                  //关闭与该客户端的链接
                    printf("client[%d] closed connection\n", sockfd);

                } else if (n < 0) {                 //出错
                    perror("read n < 0 error: ");
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
					if (res == -1)
                        perr_exit("epoll_ctl error");
                    Close(sockfd);

                } else {                            //实际读到了字节数
                    for (i = 0; i < n; i++)
                        buf[i] = toupper(buf[i]);   //转大写,写回给客户端

                   // Write(STDOUT_FILENO, buf, n);
                    Writen(sockfd, buf, n);
                }
            }
        }
    }
	
    Close(listenfd);
    Close(efd);

    return 0;
}

