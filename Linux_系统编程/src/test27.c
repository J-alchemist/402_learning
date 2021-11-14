#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define threadnum 3

void* thrd1_fun(void* arg)//函数返回值为泛型指针void *
{
	
	printf("thread 1 create finished!\n");

	return (void*)11;
	
}
void* thrd2_fun(void* arg)
{
	printf("thread 2 create finished!\n");

	pthread_exit((void* )22);
}

void* thrd3_fun(void* arg)
{
	while(1){
	
		printf("thread 3 create finished!\n");
		sleep(1);
/*若一般无函数调用，则视为无取消点，一般不能即使cancel掉该线程，可以使用pthread_testcancel函数定义取消点，cancel能即使杀掉进程*/	
		//pthread_testcancel();//定义取消点
	}

	return (void*)33;
}

//main
int main(void)
{

	pthread_t tid[threadnum];
	void* tret[threadnum] = {NULL};//指针数组：tret[i]为地址
	//创建3个线程
	pthread_create(&tid[0], NULL, thrd1_fun, NULL);	
	pthread_create(&tid[1], NULL, thrd2_fun, NULL);	
	pthread_create(&tid[2], NULL, thrd3_fun, NULL);
//----------------------------
	//线程1  阻塞等待线程退出
	pthread_join(tid[0], &tret[0]);//阻塞等待线程退出
	printf("thread 1 exit code: %d\n", tret[0]);
	
	//线程2  线程分离结束自己	
	if(!pthread_detach(tid[1]))//调用成功返回0, 而不是线程释放回收后再返回0
		printf("thread 2 detach ing!\n");
	else printf("thread 2 detach error!\n");
	//线程3 cancel杀死进程3
	sleep(3);
	pthread_cancel(tid[2]);//3s后杀死线程3
	pthread_join(tid[2], &tret[2]);
	printf("thread 3 exit code: %d\n", tret[2]);
	
/*
由于pthread_join为阻塞等待，因此主控线程不会在其他线程未结束时，
不会先结束。
*/	
	
	return 0;
	

}



