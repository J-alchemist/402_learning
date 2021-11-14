#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
  循环创建n个子进程
  哪个进程先抢到就先执行哪个，并且返回值就是该进程返回的
*/
#define  number_process  5

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
	if(i<number_process)
	{
		printf("I'm %d child, pid = %u\n", i+1, getpid());

	}else{
		printf("I'm parent\n");
		
	}
	
	return 0;
}	



