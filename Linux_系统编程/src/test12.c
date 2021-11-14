#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*匿名映射*/

int main(void)
{
	int var = 100;
	int *p = NULL;
	pid_t pid;
	
	//MAP_ANONYMOUS
	p = (int *)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	if(p == MAP_FAILED)
	{
		perror("mmap error\n");
		exit(1);
	}
	*p=1;//往映射区首地址p写入数据1
	//创建子进程去共享文件
	pid = fork();
	if(pid == 0)//子
	{
		*p = 2000;//往映射区首地址p写入数据2000
		var = 1000;//非映射区的变量，读时共享写时复制
		printf("child writing, *p = %d, var = %d\n", *p, var);
	}else{//父
		sleep(1);//此睡眠为了让子进程先写数据
		printf("parent reading, *p = %d, var = %d\n", *p, var);
		//关闭子进程
		wait(NULL);
		//释放映射区
		int ret = munmap(p, 4);
		if(ret == -1)
		{
			perror("munmap error!\n");
			exit(1);
			
		}
	}
/*
  数据var不为共享数据
  共享映射取*P值共享了
*/
	return 0;

}
