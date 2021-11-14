#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define process_num 3

/*杀死第3个子进程*/

int main(void)
{
	pid_t pid,num3_pid;
	int i;


	//raise(SIGABRT);	//发送异常终止信号
	//abort();		//cx从此处异常终止

	for(i=0;i<process_num;i++)//创建3个子
	{
		pid = fork();
			if(i==2)//保存第三个子进程pid
					num3_pid = pid;
							if(pid==0)
								break;
				
	}
	if(i<process_num)//子
	{
		while(1)
		{
			printf("child %d ,pid: %d\r\n",i+1, getpid());
			sleep(1);
			
		}

	}else//父进程
	{
		sleep(2);
		kill(num3_pid, 9);//kill(num3_pid,SIGKILL);
	
	}

	return 0;

}
