#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define process_num 3

/*杀死第3个子进程*/

int main(void)
{
	int i=0,j=0;
	int head_leftT=0;
	alarm(10);//定时1s后发信号SIGALRM终止程序
	
	//alarm(0);//取消定时器
	
	while(++i)
	{
		printf("%d\n",i);
		sleep(1);
	//time ./test14 > xfile  重定向输出到文件，并显示执行时间
		j++;
		if(j==8)//运行8s后
		{
			head_leftT = alarm(0);//获取第一次定时的剩余时间，alarm(0)并终止第一次的定时器，
			printf("head_left—time: %ds\n",head_leftT);
			alarm(4);//定时4s，想当于就定时了14s		
		}
	}

	return 0;

}
