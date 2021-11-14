#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "seqqueue.h"

int main()
{
	int i=0, a[10];

	SeqQueue *queue = SeqQueue_Create(10);
    if( queue == NULL )
    {
        return;
    }
	//向队列中放元素
	for (i=0; i<10; i++)
	{
		a[i] = i;
		SeqQueue_Append(queue, &a[i]);
	}
	//打印队列属性
	printf("the length of queue: %d \n", SeqQueue_Length(queue));
	printf("the capacity of queue: %d \n", SeqQueue_Capacity(queue));
	printf("the header of queue: %d \n", *((int *)SeqQueue_Header(queue)) );//获取队列头元素

	//出队列，删除队列元素
	while ( SeqQueue_Length(queue) > 0 )
	{
		printf("%d \n",   *( (int *)SeqQueue_Retrieve(queue) ) );
	}

	//摧毁
	SeqQueue_Destroy(queue);

	return 0;
}
