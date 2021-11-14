#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>


typedef void (*sighandler_t)(int ); //信号注册函数的模型，函数指针

void myfun(int signo)
{
	printf("Hello,world!\n");
}

int main(void)
{
	int ret=0;
	sighandler_t handler1;
	
	struct itimerval  it, oldit;

	handler1 = signal(SIGALRM, myfun);//注册SIGALRM信号的函数，待触发的函数（回调）
	if(handler1 == SIG_ERR){
		perror("signal error!");
		exit(-1);
	}

	//总定时5s
	it.it_value.tv_sec = 5;	//第一次定时xs	
	it.it_value.tv_usec = 0;//第一次定时xus
	it.it_interval.tv_sec = 3;//过多久开启下一次秒定时
	it.it_interval.tv_usec = 0;//过多久开启下一次微秒定时
	
	ret = setitimer(ITIMER_REAL, &it, &oldit);//oldit返回定时剩余的时间
	if(ret == -1){
		perror("setitimer error!");
		exit(-1);
	}

	while(1){}

	return 0;

}
