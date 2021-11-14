#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/wait.h>
 
#define number_process  5

int main(void)
{
	int i;
	pid_t pid;
	printf("xxxxxx\n");

	for(i=0; i<number_process; i++){ //循环创建5个子进程
		pid = fork();
		
		if(pid == -1){
			perror("fork error");
			exit(1);
		}else if(pid == 0)//5个子进程创建完毕，返回
				break;	
	}
	sleep(i);
	if(i == number_process)//父进程才会执行此处
	{
		printf("I'm parent, pid = %u\n", getpid());
		//------------
		//wait(NULL);//只会清理掉一个子进程①
		//printf("wait over!\n");
		//------------
	    //while(wait(NULL));//清理所有子进程	== while(waitpid(-1, NULL, 0));//非阻塞态②
		//printf("wait over!\n");
		//------------
		int wp;//阻塞态清理所有子进程③
		do{
			wp = waitpid(-1, NULL, WNOHANG);
			if(wp>0)	
				i--;
			sleep(1);
		}while(i>0);
		printf("waitpid over!\n");
		//-------------

	}else{//子进程执行
	
		printf("I'm %d child, pid = %u\n", i+1, getpid());

		
	}
	
	return 0;
}	



