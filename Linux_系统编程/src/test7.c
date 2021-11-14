#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	pid_t pid,wpid;

	int status;
	pid = fork();
	
	if(pid == 0){//子
		printf("I'm child= %d, my parent= %d, going to sleep a moment\n", getpid(), getppid());
		sleep(10);//设置时间来手动kill 进程异常输出
		printf("child die\n");//若在sleep期间被异常杀死，不会打印出此条
		exit(100);
	}else if(pid >0){//父
			wpid = wait(&status);//阻塞
			if(wpid == -1)
			{
				perror("wait error");
				exit(1);
			}
			if(WIFEXITED(status)){//正常结束
				printf("child exit with %d\n", WEXITSTATUS(status));
				
			}
			if(WIFSIGNALED(status)){//异常结束
				printf("child killed by %d\n", WTERMSIG(status));
				}
			while(1){
				printf("I'm parent ,pid = %d, myson = %d\n", getpid(), pid);
				sleep(1);
			}	
		
	}

	return 0;
}


