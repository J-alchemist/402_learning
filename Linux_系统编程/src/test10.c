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
	char *p = NULL;
	int ret;
	int fd = open("abc.txt", O_RDWR|O_CREAT, 0644);
	if(fd<0)
	{
		perror("open error");
		exit(1);
	}
	//ftruncate文件大小:4字节，已存在的文件不用，文件占位，后面写入的数据大小要小于等于这个数，对于此数会被截断
	ret = ftruncate(fd, 5);
	if(ret == -1)
	{
		perror("ftruncate error");
		exit(1);		
	}
	//4字节
	p = mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(p == MAP_FAILED)
	{
		perror("mmap error\n");
		exit(1);
	}
	//往内存映射区去写
	strcpy(p, "abc");
	//关闭映射区
	ret = munmap(p, 4);
	if(ret == -1)
	{
		perror("munmap error!\n");
		exit(1);
		
	}
	close(fd);//文件描述符（文件句柄）在映射区创建完成后
	
	return 0;


}


