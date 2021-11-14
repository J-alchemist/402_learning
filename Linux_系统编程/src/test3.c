#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	printf("xxxxxx\n");
	/*
		fork是在原来的进程创建子进程，
		子进程创建成功返回0，父进程则会返回子进程的pid号
		先返回哪个，看谁先争夺到cpu
	*/
	pid = fork();
	if(pid == -1){
		perror("fork error");
		exit(1);
	}else if(pid == 0){//子进程 getpid获取子进程pid，getppid父进程pid
			printf("I'm child: pid = %u, ppid = %u\n", getpid(), getppid());
			
	}else {
			printf("I'm parent: pid = %u, ppid = %u\n", getpid(), getppid());	
			sleep(1);//会释放当前进程对cpu的使用权			
	}
	
	//会打印两边，因为父进程接着执行，子进程从该点往后执行
	printf("YYYYYYYY\n");

	return 0;
	
}