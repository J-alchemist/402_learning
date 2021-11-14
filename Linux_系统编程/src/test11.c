#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	int var = 100;
	int *p = NULL;
	pid_t pid;
	
	int fd = open("temp.txt", O_RDWR|O_CREAT, 0644);
	if(fd<0)
	{
		perror("open error");
		exit(1);
	}
//无法调用，原因不明
	//ulink("temp.txt");//删除文件目录项，当所有进程使用完该文件后，该文件被释放
	ftruncate(fd, 5);//预设置大小5字节
	//MAP_PRIVATE
	p = (int *)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(p == MAP_FAILED)
	{
		perror("mmap error\n");
		exit(1);
	}
	*p=1;//往映射区首地址p写入数据1
	close(fd);
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
		//关闭文件
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
