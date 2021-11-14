#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
//ѡ��
0��λ��Ԫ��������һ�αȽϣ���С�ķ���0��λ�ã�
1��λ��������2�ż��Ժ��λ�ñȽϣ���С�ķ���1��λ��
�ظ�
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
		k = i; //Ѱ����СԪ�ص��±�
		for(j=i+1; j<len; j++)
		{
			if( array[j] < array[k] ) //��ʼѰ����СԪ�ص��±�
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
