#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdlib.h> 
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//锁属性修改
typedef struct mt {

	pthread_mutex_t mutex1;//锁
	pthread_mutexattr_t mutexattr1;//锁属型
} Mymutexattr;


//main
int main(void)
{
	int i;
	Mymutexattr m;
	pid_t pid;

	int* pdate=NULL;//映射区
	//创建匿名映射区
	pdate = mmap(NULL, sizeof(*pdate), PROT_READ|PROT_WRITE, MAP_SHARED| MAP_ANON, -1 ,0);
	memset(pdate, 0, sizeof(*pdate));//指针清0
	
	pthread_mutexattr_init(&m.mutexattr1);//修改mutex1属性对象
	pthread_mutexattr_setpshared(&m.mutexattr1, PTHREAD_PROCESS_SHARED);//将属性对象改为进程共享（默认线程共享）
	
	//初始化锁
	pthread_mutex_init(&m.mutex1, &m.mutexattr1);
	
	//子进程
	pid = fork();
	if(pid==0 )//子
	{
		for(i=0; i<5; i++)
		{
			pthread_mutex_lock(&m.mutex1);
			
			*pdate+=1;
			printf("--child process --------*pdate+=1: %d\n", *pdate);
			
			pthread_mutex_unlock(&m.mutex1);
			sleep(1);
		}
	
	}else if(pid >0){//父进程
	
		for(i=0; i<5; i++)
		{
			pthread_mutex_lock(&m.mutex1);
			
			*pdate += 2;
			printf("--parent process --------*pdate+=2: %d\n", *pdate);
			
			pthread_mutex_unlock(&m.mutex1);
			sleep(1);
		}	
		//父进程回收子进程
		wait(NULL);
	}else
	{
		perror("fork error");
		exit(-1);
	}

	pthread_mutexattr_destroy(&m.mutexattr1);//销毁锁属性对象
	pthread_mutex_destroy(&m.mutex1);//销毁suo

	return 0;
	
}


