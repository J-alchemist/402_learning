#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include "Myrw.h"

/*
从fd的缓冲区读取n字节数据到vptr
ssize_t: 有符号整型
size_t:  无符号整型
返回读取字节数
解释：由于socket包一次最多1500字节，只调用read函数读完1500字节（一个包）就返回了
若需要读取多于1500字节包，就需要ReadNbyte函数
*/
ssize_t ReadNbyte(int fd, void *vptr, size_t n)
{
	size_t nbleft;//剩余字节
	ssize_t nbread;//读到的字节
	char *ptr;
	
	ptr = vptr;
	nbleft = n;//未读取之前
	
	while(nbleft > 0) {
		
		nbread = read(fd, ptr, nbleft);
		if( nbread < 0 ){//read异常
			if( errno == EINTR )//被信号中断，nbread = 0重新读
				nbread = 0;
			else
				return -1;
			
		}else if(nbread == 0)//正常读完
			break;
			
		nbleft -= nbread;	//剩余字节	
		ptr += nbread;	//移动指针
	}

	return (n-nbleft);//返回读取了多少字节
}
/*
将缓冲区vptr的数据向fd的缓冲区写入n字节数据
ssize_t: 有符号整型
size_t:  无符号整型
返回写入字节数
*/
ssize_t WriteNbyte(int fd, const void *vptr, size_t n)
{
	size_t nbleft;//剩余字节
	ssize_t nbwrite;//写了的字节
	const char *ptr;

	ptr = vptr;
	nbleft = n;//未写之前

	while(nbleft > 0) {
		
		nbwrite = write(fd, ptr, nbleft);
		if( nbwrite <= 0 ){
			if(nbwrite < 0 && errno == EINTR)//写被中断,重写
				nbwrite = 0;
			else	
				return -1;
		}
		nbleft -= nbwrite;	//剩余字节	
		ptr += nbwrite;	//移动指针
		
	}
	
	return (n-nbleft);//返回写了多少字节
}

/*
从fd缓冲区读取100字节放入read_buf缓冲区
ptr传出参数
一次调用读取read_buf[100]
思想：read_buf  --->  read_ptr  --->  ptr传出
*/
static ssize_t My_read(int fd, char *ptr)
{
	static int read_cnt=0;
	static char *read_ptr;
	static char read_buf[100];
	
	if(read_cnt <= 0){
		
read_again:	
		read_cnt = read(fd, read_buf, sizeof(read_buf));
		if(read_cnt<0) {
			if(errno == EINTR)
				goto read_again;
			return -1;
		} else if(read_cnt==0)
		{
			return 0;		
		}
		//read_cnt>0
		read_ptr = read_buf;
	}
	
	read_cnt--;//字节数
	*ptr = *read_ptr++;
	
	return 1;
	
}

/*
Readline函数：从fd读取
fgets函数：只能从标准输入缓冲区读
传出参数vptr
*/
ssize_t Readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t n, ret;
	char c, *ptr;
	
	ptr = vptr;
	
	for( n = 1; n < maxlen ; n++) {
		
		ret = My_read(fd, &c);//c接收传出的字符串
		if(ret == 1){
			*(ptr++) = c;	//*ptr = c; ptr++;
			if (c == '\n')//字符串结束符
				break;
		}else if(ret == 0){
			
			*ptr = 0;
			return (n-1);
		}else
			return -1;		
	}
	
	*ptr = 0;
	
	return n;
	
}

//-------------------------------------
//函数封装（集成返回值判断及错误处理）
void perr_exit(const char *s)
{
	perror(s);
	exit(-1);
}

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	int n;
again:
	if(n = accept(fd, sa, salenptr) < 0){
		if( (errno == ECONNABORTED) || (errno == EINTR) )//被信号打断
			goto again;
		else
			perr_exit("accept error");
	}
	
	return n;
	
}
int Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    int n;

	if ((n = bind(fd, sa, salen)) < 0)
		perr_exit("bind error");

    return n;
}

int Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
    int n;

	if ((n = connect(fd, sa, salen)) < 0)
		perr_exit("connect error");

    return n;
}

int Listen(int fd, int backlog)
{
    int n;

	if ((n = listen(fd, backlog)) < 0)
		perr_exit("listen error");

    return n;
}

int Socket(int family, int type, int protocol)
{
	int n;

	if ((n = socket(family, type, protocol)) < 0)
		perr_exit("socket error");

	return n;
}

ssize_t Read(int fd, void *ptr, size_t nbytes)
{
	ssize_t n;
	
again:
	if( (n = read(fd, ptr, nbytes)) == -1 ){
		if(errno == EINTR)
			goto again;
		else
			return -1;
		
	}
	
	return n;
	
}

ssize_t Write(int fd, const void *ptr, size_t nbytes)
{
	ssize_t n;

again:
	if ( (n = write(fd, ptr, nbytes)) == -1) {
		if (errno == EINTR)
			goto again;
		else
			return -1;
	}
	return n;
}

int Close(int fd)
{
    int n;
	if ((n = close(fd)) == -1)
		perr_exit("close error");

    return n;
}









 
