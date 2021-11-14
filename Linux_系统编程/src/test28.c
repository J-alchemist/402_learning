#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

//全局互斥锁
pthread_mutex_t mutex1;


void* Myfun(void* arg)
{
	srand(time(NULL));
	
	while(1)
	{
		pthread_mutex_lock(&mutex1);//上锁
		printf("hello1 ");
		sleep(rand() % 3);
		printf("world1\n");
		
		pthread_mutex_unlock(&mutex1);
		sleep(rand() % 3);
	}
	
	return NULL;
	
}


int main(void){

	pthread_t tid;
	
	srand(time(NULL));
	
	pthread_mutex_init(&mutex1, NULL);//初始化锁，调用完后	mutex1==1
	pthread_create(&tid, NULL, Myfun, NULL);//子线程
	
	while(1){//主控线程
	
		pthread_mutex_lock(&mutex1);//上锁
		printf("hello2 ");
		sleep(rand() % 3);
		printf("world2\n");
		
		//pthread_mutex_lock(&mutex1);//上锁之后还未解锁又上锁，形成死锁，cx卡死	
		pthread_mutex_unlock(&mutex1);//解锁，若在解锁后sleep不释放cpu，则其他线程也很难抢到cpu	
		sleep(rand() % 3);
	
	}
	
	pthread_join(tid, NULL);//等待回收线程
	pthread_mutex_destroy(&mutex1);//摧毁锁
	
	return 0;

}





