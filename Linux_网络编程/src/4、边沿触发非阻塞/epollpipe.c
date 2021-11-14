#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <errno.h>
#include <unistd.h>

#define MAXLINE 	10
#define Epoll_TreeSize 10
/*
select、poll、epoll函数都是操作文件描述符，因此
	理论上是可以操作实际文件的，但是一般不用（杀鸡用牛刀）
此例：epoll操作管道，验证epoll的ET和LT触发 
每次读取写入的数据的一半，ET模式：触发一次读取，必须等待下一次写入之后再会触发读取
						  LT模式：未读取完缓冲区，可以一直触发读取

*/
int main(int argc, char *argv[])
{
    int efd, i;
    int pfd[2];
    pid_t pid;
    char buf[MAXLINE], ch = 'a';

    pipe(pfd);
    pid = fork();

    if (pid == 0) {             //子 写
        close(pfd[0]);
       // while (1) 
	//{
            //aaaa\n
            for (i = 0; i < MAXLINE/2; i++)
                buf[i] = ch;
            buf[i-1] = '\n';
            ch++;
            //bbbb\n
            for (; i < MAXLINE; i++)
                buf[i] = ch;
            buf[i-1] = '\n';
            ch++;
            //buf：aaaa\nbbbb\n
            write(pfd[1], buf, sizeof(buf));
			
           // sleep(5);//5s写一次，一次写入：aaaa、bbbb字符串
        // }
        //close(pfd[1]);

    } else if (pid > 0) {       //父 读
        struct epoll_event event;
        struct epoll_event resevent[10];        //epoll_wait就绪返回event
        int res, len;

        close(pfd[1]);
        efd = epoll_create(Epoll_TreeSize);

        event.events = EPOLLIN | EPOLLET;     // ET 边沿触发
        //event.events = EPOLLIN;                 // LT 水平触发 (默认)
        event.data.fd = pfd[0];
        epoll_ctl(efd, EPOLL_CTL_ADD, pfd[0], &event);
	sleep(1);	//等待子进程写完在进行读取操作，看到底触发几次！！！

        while (1) {
	
            res = epoll_wait(efd, resevent, Epoll_TreeSize, -1);
          //  printf("res %d\n", res);
            if (resevent[0].data.fd == pfd[0]) {
                len = read(pfd[0], buf, MAXLINE/2);//每次读一半
                write(STDOUT_FILENO, buf, len);
            }
        }

        close(pfd[0]);
        close(efd);

    } else {
        perror("fork");
        exit(-1);
    }

    return 0;
}

