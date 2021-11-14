#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <strings.h>
#include <pthread.h>

//要连接的server的ip+端口
char *ipsrc = "192.168.66.132";
#define SER_PORT 6666	//不能大于65535
#define BUF_SIZE 1024

void *do_work(void *arg)
{
	char buf[BUF_SIZE]={0};
	int numbytes=0;
	
	int *clientlistenfd = (int *)arg;
				
	while(1){
		
		numbytes = read(*clientlistenfd, buf, sizeof(buf));
		if(numbytes == 0){//判断read函数返回值

			close(*clientlistenfd);	
		}else if(numbytes == -1) {
				
			perror("read error");
			exit(-1);
			}else if(numbytes > 0) {
			
				for(int i=0; i<numbytes; i++)
				{
					buf[i] = toupper(buf[i]);//作字符转换
				}

				//发送
				write(*clientlistenfd, buf, numbytes);
				
			}	
		
		}	
	

	return NULL;
}

int main()
{
	char client_ip[32];
	pthread_t tid;
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
	inet_pton(AF_INET, ipsrc, &(saddr.sin_addr.s_addr));//ip
	int ret = bind(listenfd, (struct sockaddr*)&saddr, sizeof(saddr));//绑定ip+端口
	if(ret==-1){
		perror("bind error");
		exit(1);
	}
	//3
	listen(listenfd, 3);//允许客户端连接数
	printf("waitting client connect...\n");	
	//4
	int clistenfd;
	struct sockaddr_in  caddr;

	bzero(&caddr, sizeof(caddr));//清0
		
	while(1){
	
		socklen_t caddrlen = sizeof(caddr);
		clistenfd = accept(listenfd, (struct sockaddr*)&caddr, &caddrlen);//阻塞等待
		if(clistenfd==-1){
			perror("accept error");
			exit(1);
		}else{
					
			//线程
			pthread_create(&tid, NULL, do_work, (void *)&clistenfd);
			pthread_detach(tid);//分离线程，自动回收
			//i++;
		}
	}		


	return 0;
	
}



