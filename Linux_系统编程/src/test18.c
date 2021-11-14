#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>


void myfun(int signo)//回调函数是内核调用
{
	printf("%d signal execute!\n", signo);
	sleep(10);//可以测试再10s内，触发SIGQUIT，无反映，10s结束后才会去处理他
}

int main(void)
{
	
	int ret;
	struct sigaction act,old_act;
	
	act.sa_handler = myfun;

	sigemptyset(&act.sa_mask);//先置0
	sigaddset(&act.sa_mask, SIGQUIT);//信号捕捉函数执行期间需要屏蔽的信号SIGQUIT
	
	act.sa_flags = 0;//默认属性，信号捕捉函数执行期间自动屏蔽本信号
	
	ret = sigaction(SIGINT, &act, &old_act);//old_act可换成NULL不获取旧的值，注册SIGINT信号，ctrl+c
	if(ret < 0)
	{
		perror("sigaction error!");
		exit(-1);
	}
	
	while(1){}




	while(1){}

	return 0;

}
