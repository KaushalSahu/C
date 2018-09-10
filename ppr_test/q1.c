#include<stdio.h>
#include<stdlib.h>

int main()
{
	int n;
	int max=0;
	int max1=0;
	int pos=0;
	int len;
	scanf("%d",&n);
	scanf("%d",&len);

	char a[5][len];

	for(int i=0;i<n;i++)
		scanf("%s",&a[i][0]);

	for(int i=0;i<len;i++)
	{
		for(int j=65;j<90;j++)
		{

			int c=0;
			for(int k=0;k<n;k++)
			{
				if((char)j==a[k][i])
					c++;
			}
			if(c>max)
				max=c;
		}
		if(max>max1)
		{
			max1=max;
			pos=i;
		}
	
	}
	printf("%d",pos+1);
	printf(" : %4.1f %%",(double)max1/n*100.0);
	return 0;
}
