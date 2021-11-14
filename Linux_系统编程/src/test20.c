#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <errno.h>

void Myfun(int signo)
{

}

/*用 alarm + sigsuspend + sigaction 实现sleep函数功能*/
unsigned int Mysleep(unsigned int s)
{
	struct sigaction act,old_act;//act.sa_mask
	int ret;
	sigset_t mask, oldmask, suspmask;//信号屏蔽字集
	
	act.sa_handler = Myfun; //关联信号捕捉函数
	sigemptyset(&act.sa_mask); //置0,函数执行期间无屏蔽
	act.sa_flags = 0;
	
	ret = sigaction(SIGALRM , &act, &old_act);//捕捉SIGALRM信号
	if(ret == -1)
	{
		perror("sigaction error!");
		exit(1);
	}
	//设置阻塞信号集，屏蔽SIGALRM，先屏蔽，避险失去cpu而错失SIGALRM信号，保证在sigsuspend调用时，一定可以处理到SIGALRM信号！！！
	sigemptyset(&mask);//清空集合
	sigaddset(&mask, SIGALRM);//mask信号集中加入SIGALRM
	sigprocmask(SIG_BLOCK, &mask, &oldmask);//改变阻塞信号集
	
	//定时
	alarm(s);//之后产生SIGALRM，将被阻塞
	
	//解除的阻塞
	suspmask = oldmask;
	sigdelset(&suspmask, SIGALRM);//保证SIGALRM未被屏蔽
	
	//挂起进程，等待信号唤醒
	sigsuspend(&suspmask);
	
	ret = alarm(0);//返回定时剩余时长
	
	sigaction(SIGALRM , &old_act, NULL);//恢复SIGALRM原有的处理方式
	sigprocmask(SIG_SETMASK, &oldmask, NULL);//恢复原有的阻塞信号集
	
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



