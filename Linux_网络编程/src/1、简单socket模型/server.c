#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <strings.h>

//要连接的server的ip+端口
char *ipsrc = "127.0.0.1";
#define SER_PORT 8000	//不能大于 65535
#define BUF_SIZE 1024

/*
c开头的时客户端参数
此程序完成客户端与服务器的连接，并且服务器将客户端发送的字符转换为大写，回发
无客户端测试： nc  127.0.0.1  8000
为了不出现if-else的返回值判断，可以自己重新封装函数。。。
解释：服务器一个套接字绑定他自己的ip+端口，客户端也有自己的套接字，（绑定可省略）连接到服务器的ip+端口
*/

int main()
{
	char client_ip[INET_ADDRSTRLEN];   //#define INET_ADDRSTRLEN 16 
	//1
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);//设置为tcp网络套接字
	if(listenfd==-1){
		perror("socket error");
		exit(1);
	}
	//2
	struct sockaddr_in  saddr;
		
	bzero(&saddr, sizeof(saddr));//清空  memset
	saddr.sin_family = AF_INET;		//ipv4
	saddr.sin_port = htons(SER_PORT);	//端口
	inet_pton(AF_INET, ipsrc, &(saddr.sin_addr.s_addr));//ip地址转换 点分十进制-->网络字节序		//ip
	int ret = bind(listenfd, (struct sockaddr*)&saddr, sizeof(saddr));//绑定ip+端口
	if(ret==-1){
		perror("bind error");
		exit(1);
	}
	//3
	listen(listenfd, 128);//允许客户端连接数
	printf("waitting client connect...\n");	
	//4
	int connect_fd;
	struct sockaddr_in  caddr;

	bzero(&caddr, sizeof(caddr));
	socklen_t caddrlen = sizeof(caddr);	//因为此参数是传入传出参数
	
	//返回一个新的套接字connect_fd，用于后续数据传输操作，返回caddr客户端的ip+端口信息，客户端端口系统自动分配
	connect_fd = accept(listenfd, (struct sockaddr*)&caddr, &caddrlen);//阻塞等待！！！		接受客户端的连接，成返回客户端的sock，失败-1
	if(connect_fd==-1){
		perror("accept error");
		exit(1);
	}else 
	{

		printf("client IP:[%s] ,PORT:[%d] connect success...\n",
				inet_ntop(AF_INET, &caddr.sin_addr.s_addr, client_ip, sizeof(client_ip)), 
					ntohs(caddr.sin_port));
	}

	//5
	char buf[BUF_SIZE]={0};
	int numbytes = 0, times=0;;
	while(1){
//read、write都是操作的csock_fd，说名一个套接字在内核是以2个缓冲区实现的
		numbytes = read(connect_fd, buf, sizeof(buf));//返回读到的字节数
		if(numbytes !=0 )
		{		
			for(int i=0; i<numbytes; i++)
			{
				buf[i] = toupper(buf[i]);//作字符转换
			}
			//6
			write(connect_fd, buf, numbytes);//发送
			printf("--client request times: [%d]\n", ++times);
		}

	}


	//7
	close(listenfd);
	close(connect_fd);
	
	printf("server close...\n");

	return 0;
	
}
