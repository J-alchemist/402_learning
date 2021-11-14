#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLINE 10
#define SERV_PORT 8000
#define Epoll_TreeSize 10
/*
水平触发 约等于 边沿触发+非阻塞读，
前者多次调用epoll_wait触发，因而后者效率高
开发中多使用后者，高效率！
假设现在要读10字节数据，但是客户端发送了少于10字节数据，
如果非阻塞读处理，就不会一直卡在读函数那里
*/


int main(void)
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
    int efd, flag;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, 20);

    ///////////////////////////////////////////////////////////////////////
    struct epoll_event event;
    struct epoll_event resevent[Epoll_TreeSize];
    int res, len;

    efd = epoll_create(Epoll_TreeSize);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));//允许端口复用
    event.events = EPOLLIN | EPOLLET;  // ET 边沿触发   
    //event.events = EPOLLIN;	//(默认的水平触发)
    printf("waiting connections ...\n");
    cliaddr_len = sizeof(cliaddr);
	//阻塞等待
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
    printf("received from %s at PORT %d\n",
            inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
            ntohs(cliaddr.sin_port));
    //修改connfd为非阻塞读 
    flag = fcntl(connfd, F_GETFL);      
    flag |= O_NONBLOCK;
    fcntl(connfd, F_SETFL, flag);

    event.data.fd = connfd;
    epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &event);      //将connfd加入监听红黑树
    while (1) {
		
        //printf("epoll_wait begin\n");
        res = epoll_wait(efd, resevent, Epoll_TreeSize, -1);    //最多10个, 阻塞监听
       // printf("epoll_wait end res %d\n", res);

        if (resevent[0].data.fd == connfd) {
            while ((len = read(connfd, buf, MAXLINE/2)) >0 )    //非阻塞读, 轮询
                write(STDOUT_FILENO, buf, len);
        }
    }

    return 0;
}


