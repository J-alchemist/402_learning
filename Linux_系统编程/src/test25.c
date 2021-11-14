#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define threadnum 5

void* thrd1_fun(void* arg)
{
	int i = (int)arg;

	printf("I'm %dth thread: thread id = %lu, pid = %u\n", i+1, pthread_self(), getpid());	
	
	pthread_exit(NULL);//每个线程执行完退出
}


int main(void)
{

	pthread_t tid;
	int ret,i,retval;
	
	printf("main thread id:%lu,pid:%d-----------\n", pthread_self(), getpid());//主控线程id
	for(i=0; i<threadnum; i++){//循环创建线程
		
		ret = pthread_create(&tid, NULL, thrd1_fun, (void *)i);//i值回传递给thrd1_fun函数的参数arg
		if(ret != 0){
			fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
			exit(1);

		}
		printf("%dth  thread id:%lu-----------\n",i+1, tid);					
		
	}
	
	pthread_exit(NULL);	//主控线程退出，进程还在不影响其他线程
	//sleep(1);//主控进程必须等待时间，给子进程回调函数执行时间
	//return 0;//返回到调用者那里  echo $?获取
	//exit(0);//将整个进程退出，线程也被全部退出  echo $?获取
}


