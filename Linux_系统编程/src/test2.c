#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>//open函数一下三个
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//close函数

int main(void)
{
	int fd = open("abc.txt", O_RDWR);
	if(fd == -1)
	{
		perror("open file");
		exit(1);
	}
	//lseek获取文件长度，当调用成功时则返回目前的读写位置, 也就是距离文件开头多少个字节
	int ret = lseek(fd, 0, SEEK_END);
	printf("file lenth = %d\n", ret);
	//文件拓展，往文件末尾偏移1000个byte，空洞文件
	ret = lseek(fd, 1000, SEEK_END);
	printf("increased file lenth = %d\n", ret);
	write(fd, "123", 1);//假写完成拓展，随便写入
	
	close(fd);
	
	return 0;
}