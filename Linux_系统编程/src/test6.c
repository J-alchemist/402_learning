#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
/*使用dup2、execlp将指令输出到ps.out文件*/
int main()
{
	int fd;
	//O_TRUNC：文件长度设为0，清空
	fd = open("ps.out", O_WRONLY|O_CREAT|O_TRUNC, 0644);
	
	if(fd<0)
	{
		perror("open error");
		exit(-1);
	}
	//改变文件描述符中文件指针和标准输出的指向
	dup2(fd, STDOUT_FILENO);
	
	execlp("ps","ps","aux",NULL);
	
	return 0;
}



