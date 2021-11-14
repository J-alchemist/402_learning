#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>


char *IPSRC = "127.0.0.1";		//本地地址
#define SER_PORT 8000	//不能大于65535
#define BUF_SIZE 1024

int main(int argc, char** argv)
{
	//1
	int csock_fd = socket(AF_INET, SOCK_STREAM, 0);//设置为tcp网络套接字
	if(csock_fd==-1){
		perror("socket error");
		exit(1);
	}

	//2
	struct sockaddr_in  saddr;
	int saddrlen = sizeof(saddr);

	memset(&saddr, 0, sizeof(saddr));//清空
	saddr.sin_family = AF_INET;		//ipv4
	saddr.sin_port = htons(SER_PORT);	//端口
	inet_pton(AF_INET, IPSRC, &(saddr.sin_addr.s_addr));//ip地址转换 点分十进制-->网络字节序
	int ret = connect(csock_fd, (struct sockaddr*)&saddr, saddrlen);
	if(ret==-1){
		perror("connect error");
		exit(1);
	}
	
	//3

	char buf[BUF_SIZE];

	while(1){
/*
fgets()： "hello"  ----->   "hello\n\0",因此要用strlen获取长度

*/
		fgets(buf, sizeof(buf), stdin);//从标准输入获取数据
		//发送
		write(csock_fd, buf, strlen(buf));

		int n = read(csock_fd, buf, sizeof(buf));
	
		write(STDOUT_FILENO, buf, n);
		printf("-------------------\n");	
	}
	
	close(csock_fd);
	
	return 0;
	
}
