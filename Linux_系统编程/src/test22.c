#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
	pid_t pid;

	pid = fork();
	if(pid <0 ){
		perror("fork error");
		exit(1);
	}else if( pid==0 ){//子
		
		printf("child PID == %d\n", getpid());
		printf("child Group ID == %d\n", getpgrp());//子进程组id 等价于下面
		//printf("child Group ID == %d\n", getpgid(0));
		
		sleep(6);//等待父进程改变进程的id
		printf("child Group ID changed to: %d\n", getpgid(0));
		exit(0);
	}else if( pid>0 ){//父
		sleep(1);
		setpgid(pid, pid);//将子进程加入到进程组
		sleep(3);
		
		printf("\n");
		printf("parent PID == %d\n", getpid());
		printf("parent Group ID == %d\n", getpgid(0));

		printf("parent's parent PPID == %d\n", getppid());//执行该进程的shell终端		
		sleep(5);
		setpgid(getpid(), getppid());//将父进程加入到进程组
		printf("parent Group ID == %d\n", getpgid(0));
		printf("%d\n", flag);
		
		
		
	}
                
	return 0;

}





