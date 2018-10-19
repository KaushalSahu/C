#include<stdio.h>
int main()
{
	int n;
	int i;
	int j;
	int sum;
	int flag = 1;
	scanf("%d",&n);
	int a[n][n];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			scanf("%d",&a[i][j]);
	}

	for(i=0;i<n;i++)
	{
		sum = 0;
		j = i;

		if(i!=n-1 && i==0 && j==0)
			sum = a[i][j+1]+a[i+1][j];
		else if(i==n-1 && j==n-1)
			sum = a[i-1][j]+a[i][j-1];
		else
			sum =a[i-1][j]+a[i][j-1]+a[i][j+1]+a[i+1][j];

		if(a[i][i] != sum)
			flag = 0;

	}
	if(flag == 0)
		printf("no");
	else
		printf("yes");

	return 0;
}
