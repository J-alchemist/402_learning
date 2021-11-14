#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h> 
#include <unistd.h>

//链表
struct msg {
	struct msg* next;
	int num;

};
struct msg* head = NULL;//头指针
struct msg* mp = NULL;//节点

/*生产者消费者模型*/
//条件变量,静态初始化（可以不使用init函数）
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
//全局互斥锁
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;


void* Consumer(void* arg)
{
	
	while(1)
	{
		pthread_mutex_lock(&mutex1);//上锁
		
		while(head == NULL){
			pthread_cond_wait(&cond1, &mutex1);//等待条件变量满足，解锁
		}
		mp = head;
		head = mp->next;	//模拟消费掉一个产品
		
		pthread_mutex_unlock(&mutex1);//解锁
		
		printf("Consumer-----%d\n", mp->num);
		
		free(mp);
		mp = NULL;
		
		sleep(rand() % 10);
		
	}
	
	return NULL;
	
}


int main(void){

	pthread_t tid;
	
	srand(time(NULL));//随机数种子
	
	pthread_create(&tid, NULL, Consumer, NULL);//创建子线程
	
	while(1){//主控线程-product
	
		mp = malloc(sizeof(struct msg));
		mp->num = rand() % 400 + 1;	//模拟生产一个产品
		printf("--Product ----%d\n", mp->num);	
		
		pthread_mutex_lock(&mutex1);//上锁
		mp->next = head;
		head = mp;
		pthread_mutex_unlock(&mutex1);//解锁
		
		pthread_cond_signal(&cond1);//唤醒某个阻塞在条件变量上的进程
		//pthread_cond_broadcast(&cond1);//唤醒所有阻塞在条件变量上的进程
		sleep(rand() % 5);
	}
//--------------------------------------------------------	
	//等待回收线程
	pthread_join(tid, NULL);
	pthread_mutex_destroy(&mutex1);//摧毁互斥锁
	pthread_cond_destroy(&cond1);//摧毁条件变量

	
	return 0;

}





