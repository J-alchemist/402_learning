#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include "wrap.h"

#define SERV_PORT 8000
char *IPSRC = "127.0.0.1";
/*
select支持最多1024，FD_SETSIZE
描述符集合：实质也就是位图，即为一串0101010码
select：监听是否有新的连接请求、监听是否有已连接客户端新的数据传输
连接请求的fd是读集合
*/
int main(int argc, char *argv[])
{
    int i, n, maxi=-1;  //maxi存放client最新的下标注 

    int nready, client[FD_SETSIZE];         //client存储每个连接的客户端的fd值
    int maxfd, listenfd, connfd, sockfd;	//connfd建立连接后用于通信的描述符
    char buf[BUFSIZ], str[INET_ADDRSTRLEN];         // #define INET_ADDRSTRLEN 16 

    struct sockaddr_in clie_addr, serv_addr;//存储套接字待绑定的ip+端口等信息
    socklen_t clie_addr_len;
    fd_set rset, allset;    //rset读描述符集合、allset用来进行中间的操作  
//----------------------------
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);//建立套接字

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));//允许端口复用

    bzero(&serv_addr, sizeof(serv_addr));//清0
    serv_addr.sin_family= AF_INET;
    //serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//系统分配一个主机ip
	inet_pton(AF_INET, IPSRC, &(serv_addr.sin_addr.s_addr));//自己定义ip
    serv_addr.sin_port= htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));//服务器套接字绑定自身ip+端口
    Listen(listenfd, 128);

    maxfd = listenfd;   //此时 listenfd文件描述符 除了标准输入0输出1错误2外，的第一个描述符3  记录当前最大的描述符

    for (i = 0; i < FD_SETSIZE; i++)//初始化client[]数组的默认状态为-1
        client[i] = -1;         

    FD_ZERO(&rset);//文件描述符清0
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);//将描述符集合的

    while (1) { 

	//----------------------------connect require---------
        rset = allset; //将每次设置完的集合赋予。。。
		//监听连接请求，最后一个参数设置定时监控时间，NULL：阻塞监控下去
		//select函数传入rset，传出的rset只含动作了的描述符
		//返回值：多少个动作了的fd
        nready = select(maxfd+1, &rset, NULL, NULL, NULL);// maxfd = listenfd 第一个参数：监控的最大文件描述符+1
        if (nready < 0)
            perr_exit("select error");

        if (FD_ISSET(listenfd, &rset)) { //判断传出的rset集合是否有listenfd描述符

            clie_addr_len = sizeof(clie_addr);
			//返回的connfd描述符，从4开始，3是listenfd
            connfd = Accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);//Accept 不会阻塞
            printf("received from %s at PORT %d\n",
                    inet_ntop(AF_INET, &clie_addr.sin_addr, str, sizeof(str)),
                    ntohs(clie_addr.sin_port));
			//前面client初始化为-1
            for (i = 0; i < FD_SETSIZE; i++)
                if (client[i] < 0) {  //找client[]中没有使用的位置，保存accept返回的文件描述符
                    client[i] = connfd;      //第一个客户端连接进来的描述符 存储在 client[0]                 
                    break;
                }
			//达到select能监控的文件个数上限 1024
            if (i == FD_SETSIZE) { 
                fputs("too many clients\n", stderr);
                exit(1);
            }
			//向监控文件描述符集合allset添加新的文件描述符connfd
            FD_SET(connfd, &allset); 
			//更新最大的fd号			
            if (connfd > maxfd)//maxfd最开始是3：listenfd
                maxfd = connfd; 

            if (i > maxi)
                maxi = i;  //更新最新的fd下标

            if (--nready == 0)//nready = 1 且 FD_ISSET(listenfd, &rset)==1 -->则只有连接请求，就不执行后面的数据请求
                continue;
        } 
	//-------------------------data deal-----------
        for (i = 0; i <= maxi; i++) {    //遍历每个fd
			sockfd = client[i];	
            if (sockfd < 0)//无任何动作，client初始化为-1
                continue;
			
            if (FD_ISSET(sockfd, &rset)) {

                if ((n = Read(sockfd, buf, sizeof(buf))) == 0) {    //==0，读socket为0表示对端关闭了
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);                       //从集合里面解除
                    client[i] = -1;
                } else if (n > 0) {		//正常处理
                    for (int j = 0; j < n; j++)
                        buf[j] = toupper(buf[j]);
                    Write(sockfd, buf, n);
                    Write(STDOUT_FILENO, buf, n);//服务器输出处理的数据
                }
                if (--nready == 0)
                    break;           //只有一个数据请求，直接跳出for
            }
        }
    }
	
    Close(listenfd);
    return 0;
}

