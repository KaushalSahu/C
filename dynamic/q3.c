#include<stdio.h>
#include<stdlib.h>

void print(int capacity,int n,int* temp)
{
	printf("capacity = %2d; size = %2d; elements = ", capacity, n);
	for(int i=0;i<n;i++) 
		printf(" %d",temp[i]);
	printf("\n");

}

int* shift(int *temp, int *len, int index)
{	
	for(int i=index;i<*len;i++)	
		temp[i]=temp[i+1];
	(*len)--;

	return temp;
}

int* pop_back(int* temp, int *capacity, int *len, int index, int ch)
{

	if(ch==1)
	{
		temp = shift(temp, len, index);
	}

	if(ch==2)
	{
		for(int i=0;i<*len;i++)	
		{
			if(temp[i]==index)
			{
				temp = shift(temp, len, i);
				break;
			}
		}

	}
	if(ch==3)
	{
		for(int i=0;i<*len;i++)	
		{
			if(temp[i]==index)
			{
				temp = shift(temp, len, i);
				i--;
			}
		}

	}
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
	int n, *temp, capacity, index, val, val2;
	scanf("%d",&capacity);
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++) 
	{
		scanf("%d",&a[i]);
	}
	//pop operation
	scanf("%d",&index);
	scanf("%d",&val);
	scanf("%d",&val2);
	temp=a;
	temp  = pop_back(temp, &capacity, &n, index, 1);
	temp  = pop_back(temp, &capacity, &n, val, 2);
	temp  = pop_back(temp, &capacity, &n, val2, 3);
}

