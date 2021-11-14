#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
//选择法
0号位置元素与其他一次比较，最小的放在0号位置，
1号位置依次与2号及以后的位置比较，最小的放在1号位置
重复
*/
void printArray01(int array[], int len)
{
	int i = 0;
	for(i=0; i<len; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

void swap01(int array[], int i, int j)
{
	int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

void SelectionSort(int array[], int len) // O(n*n)
{
	int i = 0;
	int j = 0;
	int k = 0;

	for(i=0; i<len; i++)
	{
		k = i; //寻找最小元素的下标
		for(j=i+1; j<len; j++)
		{
			if( array[j] < array[k] ) //开始寻找最小元素的下标
			{
				k = j;
			}
		}
		swap01(array, i, k);
	}
}

int main01()
{
	int array[] = {12, 5, 433, 253, 10, 1};
	int len = sizeof(array) / sizeof(*array);

	printArray01(array, len);
	SelectionSort(array, len);
	printArray01(array, len);

	system("pause");
	return 0;
}
