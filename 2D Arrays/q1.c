#include<stdio.h>
int main()
{
	int n;
	int a;
	int i;
	int sum;
	sum = 0;
	scanf("%d",&n);
	for(i=0;i<n;i++)
		{
			scanf("%d",&a);
			sum+=a;
		}

	for(i=0;(((n*n)-n)*i<sum);i++);
	printf("%d\n",i);
	return 0;
}
