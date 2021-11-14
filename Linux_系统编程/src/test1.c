#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>//open函数一下三个
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//close函数

int main()
{
	//只读打开当前目录下的abc.txt文件
	int fd = open("abc.txt", O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		exit(1);
	}
	//创建并只写一个文件newfile，给权限664（八进制）
	int fd1 = open("newfile", O_CREAT | O_WRONLY, 0664);
	if(fd1 == -1)
	{
		perror("open1");
		exit(-1);
	}
	//先次读10	
	char buf[10] = {0};
	int count = read(fd, buf, sizeof(buf));
	if(count == -1)
	{
		perror("read");
		exit(1);
	}
	//count>=0时，正常读出
	while(count)
	{
		int ret = write(fd1, buf, count);
		printf("write bytes:[%d]\n", ret);
		count = read(fd, buf, sizeof(buf));
	}
	
	close(fd);
	close(fd1);
	
	return 0;
	
}