#include<stdio.h>
void sort(int n,int a[][n])
{
	int i;
	int j;
	int k;
	//Sorting 2D Array
	for(i = 0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			for (k = 0; k < n - j - 1; k++) 
			{ 
				if (a[i][k] > a[i][k + 1]) 
				{ 
					int t = a[i][k]; 
					a[i][k] = a[i][k + 1]; 
					a[i][k + 1] = t; 
				}
			}
		}
	}
	//Printing 2D Array row wise
	for(i = 0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(j==0)
				printf("%d ",a[i][j]);

			else if(a[i][j]!=a[i][j-1])
				printf("%d ",a[i][j]);
		}
		printf("\n");
	}


}
int main()
{
	int i;
	int j;
	int n;
	int k;
	int flag;
	int temp;
	scanf("%d",&n);
	int arr[n*n];
	int a[n][n];
	int col[n][n];
	int c;
	c=0;
	for(i = 0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
			col[j][i] = a[i][j];
			arr[c++]=a[i][j];
		}
	}
	puts("\nAlong Rows:");
	sort(n,a);
	puts("\nAlong Columns:");
	sort(n,col);
	puts("\nMatrix:");
	//Sorting 1D Array
	for (i = 0; i < n*n; ++i) 
	{

		for (j = i + 1; j < n*n; ++j)
		{

			if (arr[i] > arr[j]) 
			{

				temp =  arr[i];
				arr[i] = arr[j];
				arr[j] = temp;

			}

		}

	}
	//Printing unique elements in 1D Array
	for(i = 0;i<n*n;i++)
	{
		flag = 1;
		for(j=i-1;j>=0;j--)
		{
			if(arr[i]==arr[j])
			{
				flag = 0;
				break;
			}
		}
		if(flag == 1)
			printf("%d ",arr[i]);
	}

	return 0;
}
