#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
/*管道为单向通道*/
int main(void)
{
	int fd[2];
	pid_t pid;
	
	int ret = pipe(fd);
	if(ret == -1)
	{
		perror("pipe error!\n");
		exit(1);
	}

	pid = fork();
	if(pid == -1){
		perror("fork error!\n");
		exit(1);
	}else if(pid ==0){//子  认为规定fd[0]读  fd[1]写
		//禁止子进程写，可读
		close(fd[1]);
		char buf[1024];
		int count = read(fd[0], buf, sizeof(buf));//读成功，返回字节数
		 if(count == -1){
			 printf("child read error!\n");	
		 }
		write(STDOUT_FILENO, buf, count);
	}else {//父
		//禁止父进程读，可写
			close(fd[0]);
			char *str = "abcdefghijklmnopqrstuvwxyz";
			write(fd[1], str ,strlen(str));
	}
	
	return 0;
}