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
//要连接的server的ip+端口
char *ipsrc = "192.168.66.132";
#define SER_PORT 6666	//不能大于65535
#define BUF_SIZE 1024

void wait_sonProcess(int signo)
{
	while(waitpid(0, NULL, WNOHANG)>0);

	return ;
}

int main()
{
	char client_ip[32];
	pid_t pid;
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
	//printf("waitting client connect...\n");	
	//4
	int clistenfd;
	struct sockaddr_in  caddr;

	bzero(&caddr, sizeof(caddr));
		
	while(1){
		socklen_t caddrlen = sizeof(caddr);	//因为此参数是传入传出参数
		clistenfd = accept(listenfd, (struct sockaddr*)&caddr, &caddrlen);
		if(clistenfd==-1){
			perror("accept error");
			exit(1);
		}
		printf("client IP:[%s] ,PORT:[%d] connect success...\n", 
			inet_ntop(AF_INET, &caddr.sin_addr.s_addr, client_ip, sizeof(client_ip)), ntohs(caddr.sin_port));
		//创建子进程
		pid = fork();
		if(pid < 0){
			perror("fork error");	
			exit(-1);	

		}else if(pid == 0){//子进程
			close(listenfd);//禁止子进程再接收客户端
			break;
		}else{	//父进程
		
			close(clistenfd);
			//注意回收子进程，否则僵尸进程很多
			signal(SIGCHLD, wait_sonProcess);
		
		
		}
	}
	//--------------数据处理
	if(pid==0){
	
		char buf[BUF_SIZE]={0};
		int numbytes=0;
		
		
		while(1){
		
			numbytes = read(clistenfd, buf, sizeof(buf));
			if(numbytes == 0){//判断read函数返回值
				close(clistenfd);	
			}else if(numbytes == -1) {
				
				perror("read error");
				exit(-1);
			}else if(numbytes > 0) {
			
				for(int i=0; i<numbytes; i++)
				{
					buf[i] = toupper(buf[i]);//作字符转换
				}
				//发送
				write(clistenfd, buf, numbytes);
			
			}	
		
		}
	}

		


	return 0;
	
}



