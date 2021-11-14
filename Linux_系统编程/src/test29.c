#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/*读时共享，写时独占，并行阻塞写锁优先*/
//全局读写锁
pthread_rwlock_t rwlock1;

//全局资源
int number=0;

void* Myfun_write(void* arg)
{
	printf("pthread1 Myfun_write is working!-----------\n");
	while(1){
		pthread_rwlock_wrlock(&rwlock1);//写枷锁
		
		printf("pthread1 is writing: [number]=%d\n", ++number);
		
		pthread_rwlock_unlock(&rwlock1);//解锁
		sleep(1);//释放cpu
	}	

	pthread_exit((void* )0);
}

void* Myfun_read(void* arg)
{
	printf("pthread3 Myfun_read is working!------------\n");
	while(1)
	{

		pthread_rwlock_rdlock(&rwlock1);//读枷锁
		
		printf("pthread3 is reading: [number]=%d\n", number);
		
		pthread_rwlock_unlock(&rwlock1);//解锁
		sleep(1);//释放cpu
	}
	
	pthread_exit((void* )0);


}
//main
int main(void)
{
	pthread_t tid[2];

	pthread_rwlock_init(&rwlock1, NULL);//初始化读写锁

	pthread_create(&tid[0], NULL, Myfun_write, NULL);//子线程1
	pthread_create(&tid[1], NULL, Myfun_read, NULL);//子线程3

	//等待回收线程
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	//摧毁锁
	pthread_rwlock_destroy(&rwlock1);

	return 0;
}


