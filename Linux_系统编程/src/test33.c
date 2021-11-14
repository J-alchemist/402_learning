#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

/*
测试时同时打开本cx: ./test33 33TEST.txt          ./test33 33TEST.txt
注意，多进程读锁共享，写锁独享
*/

int main(int argc, char** argv)
{
	struct flock myflock;//suo属性
	
	int fd;
	pid_t pid;
	
	if(argc == 2)
	{
		fd = open(argv[1], O_RDWR);
		if(fd <0){
			perror("open error");
			exit(1);
		}
	}else
	{
		perror("arg error");
		exit(1);
	}
	//设置
	//myflock.l_type = F_RDLCK;//读锁进行枷锁
	myflock.l_type = F_WRLCK;//写锁加锁
	myflock.l_whence = SEEK_SET;//文件开始位置开始加锁
	myflock.l_start = 0;	//文件起始便宜
	myflock.l_len = 0;	//整个文件枷锁
	
	fcntl(fd, F_SETLKW, &myflock);	//加锁，F_SETLKW阻塞性加锁
	
	printf("add f_lock!\n");
	sleep(10);
	
	myflock.l_type = F_UNLCK;	//修改myflock.l_type属性，变为解锁
	fcntl(fd, F_SETLKW, &myflock);
	printf("free f_lock!\n");
	
	
	return 0;
	
}


