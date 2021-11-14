#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/*
定义返回值
还有一种，在主函数申请空间，利用pthread_create函数的第四个参数传参给arg，最后也由主函数free
*/

void* thrd1_fun(void* arg)//函数返回值为泛型指针void *
{

/*
//指针传
	//int* ReturnStatus = 1;//错误，此时1被认为是地址，见文件1.c验证
	int* ReturnStatus = (int* )malloc(sizeof(int));//函数malloc分配的空间必须free才会释放
	*ReturnStatus = 1;

	printf("thrd1_fun execute over!\n");
	pthread_exit((void* )ReturnStatus);
*/

	printf("thrd1_fun execute over!\n");
	pthread_exit((void* )1);//直接传值

}


int main(void)
{

	pthread_t tid;
	int ret=0;


	ret = pthread_create(&tid, NULL, thrd1_fun, NULL);
	if(ret != 0){
		fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
		exit(1);
	}
/*

//1：理解int* TReturnStatus = ReturnStatus;
	int* TReturnStatus=NULL;
	pthread_join(tid, (void **)&TReturnStatus);//阻塞等待线程tid 退出，顺便获取退出状态,不关心退出状态可以写NULL
	printf("%d\n", *TReturnStatus);//！！
	
	free(TReturnStatus);//释放线程函数里的指针，因为TReturnStatus关联了线程函数里申请的空间ReturnStatus，所以释放TReturnStatus就可以了
*/
//2：  理解int* TReturnStatus = (void*) 1
	int* TReturnStatus=NULL;
	pthread_join(tid, (void **)&TReturnStatus);
	printf("%d\n", TReturnStatus);//！！
	
	sleep(1);

	return 0;

	
}



