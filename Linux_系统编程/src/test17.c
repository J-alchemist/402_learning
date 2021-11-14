#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>


int main(void)
{
	sigset_t myset, oldset, ped;//自定义信号集，oldset保存原来阻塞信号集，ped保存未决信号集
	int ret;
	
	sigemptyset(&myset);	//信号集置0
	sigaddset(&myset, SIGQUIT);//置1表示要屏蔽的信号位，ctrl+\可以产生该信号SIGQUIT
	sigaddset(&myset, SIGTSTP);//ctrl+z为SIGTSTP
	//注意多信号屏蔽不能写为：sigaddset(&myset,SIGQUIT|SIGTSTP）！！！
	ret = sigprocmask(SIG_BLOCK, &myset, &oldset);//屏蔽信号（操作自定义信号集去影响阻塞信号集）
	if(ret == -1)
	{
		perror("sigprocmask error!");
		exit(-1);
	}
	while(1){
		sigpending(&ped);//取出当前的未决信号集，可以配合ctrl+\产生信号看看未决信号集的变化
		for(int i=1; i<32; i++){
		
			if(sigismember(&ped, i) == 1)
			{
				putchar('1');
			}else
			{
				putchar('0');
			}
			
		}
		printf("\n");
		sleep(1);
	}
	

	return 0;

}
