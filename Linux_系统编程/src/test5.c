#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	
	pid = fork();
	
	if(pid == -1){
		perror("fork error");
		exit(-1);
	}else if(pid > 0){
		sleep(1);
		printf("parent");
		sleep(1);
	}else{
		execlp("ls", "ls","-l", NULL);//子进程调用ls -l，一般调用系统程序
		//execl("/bin/ls", "-l", NULL);//调用路径+程序名，一般调用自己的程序

	}
	
	return 0;
}