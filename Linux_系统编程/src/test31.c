#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h> 
#include <unistd.h>
#include <semaphore.h>

/*环形队列实现生产者消费者模型*/

#define NUM 5

int queue[NUM];//全局数组实现环形队列
sem_t blank_number,product_number;//空格信号量，产品信号量

void* Product(void* arg)
{
	int i=0;
	
	while(1){
	
		sem_wait(&blank_number);//将空格子信号量-1，生产量一个产品，减为0阻塞等待
		//rand() % 1000产生：0-99
		queue[i] = rand() % 100 + 1;	//产生1-100
		printf("Product--------%d\n", queue[i]);
		
		sem_post(&product_number);//产品信号量+1
		
		i = (i+1) % NUM;//移动数组下标形成环
		
		sleep(rand()%2);
	}

}

void* Consumer(void* arg)
{
	int i=0;
	while(1){
	
		sem_wait(&product_number);//将产品信号量-1，消费一个产品，减为0阻塞等待		
		printf("---Consumer--------%d\n", queue[i]);
		queue[i] = 0;
		
		sem_post(&blank_number);//空格子信号量+1
		
		i = (i+1) % NUM;
		sleep(rand()%2);
	}	
	
}


int main(void)
{

	pthread_t tid[2];
	
	srand(time(NULL));//随机数种子
	
	sem_init(&blank_number, 0, NUM);//空格子信号量初始化为NUM
	sem_init(&product_number, 0, 0);//产品信号量初始化为0
	
	pthread_create(&tid[0], NULL, Product, NULL);//创建子线程
	pthread_create(&tid[1], NULL, Consumer, NULL);


	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	sem_destroy(&blank_number);
	sem_destroy(&product_number);
	
	return 0;
}






