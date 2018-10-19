#include<stdio.h>
#include<string.h>
int main()
{
	int i;
	int j;
	int k;
	int n;
	int flag;
	scanf("%d",&n);
	char str[n][30];
	for(i = 0;i<n;i++)
	{
		scanf("%s",str[i]);
	}
	for(i=0;i<n;i++)
	{
		j=0;
		k=strlen(str[i])-1;
		flag = 0;
		while(j<k && str[i][j]==str[i][k])
		{
			j++;
			k--;
			flag = 1;
		}
		if(flag == 1 && j==k || j-1==k)
			printf("yes\n");
		else 
			printf("no\n");
	}
	return 0;
}
