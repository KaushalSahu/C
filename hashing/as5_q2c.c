#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct hash
{
	int val;
};

void hashinit(struct hash *ht[])
{
	for(int i=0;i<26;i++)
	{
		struct hash *temp=(struct hash*)malloc(sizeof(struct hash));
		temp->val=0;
		ht[i]=temp;
	}
}

void insert(int i,char a[][100],struct hash *ht[]) 
{
	int c=0;
	while(c!=strlen(a[i])) 
	{
		int hashIndex=a[i][c]%97;
		struct hash *temp=(struct hash*)malloc(sizeof(struct hash));
		temp->val=1;
		ht[hashIndex]=temp;
		c++;
	}
}

void print(struct hash *ht[])
{
	for(int i=0;i<26;i++)
	{
		if(ht[i]->val!=0)
		{
			printf("%c ",(char)i+97);
		}
	}
	printf("\n");
}

int main()
{
	int n;
	scanf("%d",&n);
	char a[n][100];
	for(int i=0;i<n;i++)
	{
		scanf("%s",&a[i][0]);
	}

	for(int i=0;i<n;i++)
	{
		struct hash *ht[26];
		hashinit(ht);
		insert(i,a,ht);
		print(ht);
	}
	return 0;
}
