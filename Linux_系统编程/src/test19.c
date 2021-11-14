#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <errno.h>

void Myfun(int signo)
{

}

/*用alarm+pause+sigaction实现sleep函数功能*/
unsigned int Mysleep(unsigned int s)
{
	struct sigaction act,old_act;
	int ret;
	
	act.sa_handler = Myfun;
	sigemptyset(&act.sa_mask); //执行期间不屏蔽
	act.sa_flags = 0;
	
	ret = sigaction(SIGALRM , &act, &old_act);//捕捉SIGALRM信号
	if(ret == -1)
	{
		perror("sigaction error!");
		exit(1);
	}
	
	alarm(s);
	ret = pause();//开始挂起当前进程，后面的暂不执行，等待信号唤醒
	if(ret == -1 && errno == EINTR)
	{
		printf("pause success!\n");
	}
	
	ret = alarm(0);//返回定时剩余时长
	sigaction(SIGALRM , &old_act, NULL);//恢复SIGALRM原有的处理方式
	
	
	return ret;
}


int main(void)
{
	while(1){
	
		Mysleep(3);
		printf("-------------------\n");
	
	}

	return 0;
}



