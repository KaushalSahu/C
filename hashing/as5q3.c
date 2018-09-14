#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct hash
{
	char ch[30];
	int count;
};


void hashinit(struct hash *ht[],int n)
{

	struct hash *item = (struct hash*) malloc(sizeof(struct hash));
	strcpy(item->ch,"");
	item->count=0;
	for(int i=0;i<n;i++)
		ht[i]=item;

}
void insert(int n,char a[][30],struct hash *ht[]) 
{
	int c=0;

	struct hash *item = (struct hash*) malloc(sizeof(struct hash));
	strcpy(item->ch,a[0]);
	item->count=1;

	int j=0;
	ht[0]=item;

	for(int i=1;i<n;i++)
	{
	
		int flag=0;

		j=c;
		while(j>=0)
		{
			//printf("\n%d %s",j,ht[j]->ch);
			if((strcmp(a[i],ht[j]->ch))==0)
			{
			printf("if  %d",j);
				flag=1;
				break;
			}
			j--;
		}

		if(flag==0)
		{
		printf("%d",i);
		strcpy(a[i],ht[i]->ch);
		item->count=1;
		ht[c]=item;
			c++;
			printf("\n%s",a[i]);
		 
		}
	}
}

void print(struct hash *ht[],int n)
{
	int c=0;
	for(int i=0;i<n;i++)
	{
		if(ht[i]->count==1)
		{
			c++;
		}
	}
	printf("%d",c);
	printf("\n");
}
int main()
{
	int n;
	scanf("%d",&n);
	char a[n][30];
	for(int i=0;i<n;i++)
	{
		scanf("%s",&a[i][0]);
	}
	struct hash *ht[n];
	hashinit(ht,n);
	insert(n,a,ht);
	print(ht,n);

}
