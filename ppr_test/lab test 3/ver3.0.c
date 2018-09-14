#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
struct node
{
	int data;
	struct node *next;
};
struct node *newnode(int x)
{
	struct node *t;
	t = (struct node *)malloc(sizeof(struct node));
	t->data = x;
	t->next = NULL;
	return t;
}
int insert(struct node **hd,int sum)
{
	while (*hd)
	{
		if ((*hd)->data == sum)
			return 0;
		
		hd = &((*hd)->next);
	}
	*hd = newnode(sum);

	return 1;
}
int square(int x)
{
	return x*x;
}
int main()
{
	int i;
	int j;
	int n;
	int sum1;
	int sum2;
	int l;
	int count=0;
	
	struct node *hd[2700];
	
	scanf("%d", &n);
	getchar();

	char a[n][11];

	for (i = 0; i < n; i++){
		
		scanf("%s",a[i]);
		getchar();
	}

	for (i = 0; i < (n-1); i++)
	{
		sum1 = 0;
		l = strlen(a[i]);

		for (j = 0; j < l; j++)
		{
			sum1+= (a[i][j] - 97) * square(j+1);
		}
		
		sum2 = 0;
		l = strlen(a[i + 1]);
		
		for (j = 0; j < l; j++)
		{
			sum2+= (a[i+1][j] - 97) * square(j+1);
		}	
	
		if( insert(&hd[sum1],sum2) )
			count++;
		
	}
	printf("%d\n",count);
}
