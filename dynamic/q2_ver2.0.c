#include<stdio.h>
#include<stdlib.h>

void print(int capacity,int n,int* temp)
{
	printf("capacity = %2d; size = %2d; elements = ", capacity, n);
	for(int i=0;i<n;i++) 
		printf(" %d",temp[i]);
	printf("\n");

}

int* pop_back(int* temp, int *capacity, int *len)
{
	(*len)--;
	
	if(*capacity >= (4*(*len)))
	{
		*capacity=(*capacity)/2;
		int *temp2=(int *)malloc(sizeof(int)*(*capacity));
		for(int i=0;i<(*len);i++) 
		{
			temp2[i]=temp[i];
		}

		temp=temp2;
	}
	print(*capacity,*len,temp);
	return temp;
}

int main()
{
	int n, *temp, capacity, n1;
	scanf("%d",&capacity);
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++) 
	{
		scanf("%d",&a[i]);
	}
	//pop operation
	scanf("%d",&n1);
	temp=a;
	for(int i=0;i<n1;i++) 
		temp = pop_back(temp, &capacity, &n);
}

