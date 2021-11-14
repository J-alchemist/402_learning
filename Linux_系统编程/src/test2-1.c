#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
/*
可以stat 文件名 根据显示信息查看一下变量的意思
   struct stat {
               dev_t     st_dev;        
               ino_t     st_ino;        
               mode_t    st_mode;       
               nlink_t   st_nlink;       
               uid_t     st_uid;        
               gid_t     st_gid;         
               dev_t     st_rdev;        
               off_t     st_size;       
               blksize_t st_blksize;  
               blkcnt_t  st_blocks; 
		}
*/
int main(int argc, char** argv)
{
	struct stat sbuf;

	int ret = stat(argv[1], &sbuf);//获取文件信息
	if(ret ==-1){
		perror("stat error");
		exit(1);
	}

	printf("file size: %ld\n", sbuf.st_size);//文件大小

	return 0;
}
