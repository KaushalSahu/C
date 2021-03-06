#include<stdio.h>
#include<stdlib.h>

void print(int capacity,int n,int* temp)
{
	printf("capacity  =  %2d; size  =  %2d; elements  =  ", capacity, n);
	for(int i = 0;i<n;i++) 
		printf(" %d",temp[i]);
	printf("\n");

}

int* push_back(int *temp, int a,int i,int *capacity )
{
	int *temp2;

	if(*capacity == i)
	{
		if(*capacity == 0)
		{
			*capacity = 1;
			temp = (int*)malloc(sizeof(int)*(*capacity));
			temp[i] = a;
		}
		else
		{
			*capacity = *capacity*2;
			temp2 = (int*)malloc(sizeof(int)*(*capacity));
			for(int j = 0;j<i;j++) 
				temp2[j] = temp[j];
			temp2[i] = a;
			free(temp);
			temp = temp2;
		}
	}
	else
	{
		temp[i] = a;
	}
	return temp;
}

int* pop_back(int* temp, int *capacity, int *len)
{
	(*len)--;

	if(*capacity >=  (4*(*len)))
	{
		*capacity /= 2;
		int* temp2 = (int *)malloc(sizeof(int)*(*capacity));
		for(int i = 0;i<(*len);i++) 
		{
			temp2[i] = temp[i];
		}
		free(temp);
		temp = temp2;
	}
	print(*capacity,*len,temp);
	return temp;
}

int main()
{
	int n, *temp, capacity = 0, a, n1;
	//push operation
	scanf("%d",&n);
	for(int i = 0;i<n;i++) 
	{
		scanf("%d",&a);
		temp  =  push_back(temp,a,i,&capacity);
	}
	//pop operation
	scanf("%d",&n1);
	for(int i = 0;i<n1;i++) 
		temp   =  pop_back(temp, &capacity, &n);
}

