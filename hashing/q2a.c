#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	int data;
	struct node *next;
};

struct hash
{
	int key;
	struct node *value;
};

void hashinit(struct hash *ht[])
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp = NULL;

	for(int i = 0; i < 26; i++)
	{
		struct hash *item = (struct hash*) malloc(sizeof(struct hash));
		item->key = i;
		item->value = temp;
		ht[i] = item;
	}

}

void insert(int i,char a[][100],struct hash *ht[]) 
{
	int c=0;
	while(c!=strlen(a[i])) 
	{
		struct hash *item = (struct hash*) malloc(sizeof(struct hash));
		struct node *val = (struct node*)malloc(sizeof(struct node));

		val->data=a[i][c];
		val->next=NULL;
		int hashIndex = a[i][c]%97;

		struct node *temp=(struct node*)malloc(sizeof(struct node));
		temp=ht[hashIndex]->value;

		while(temp!=NULL && temp->next!=NULL)
			temp=temp->next;

		if(temp==NULL)
			temp = val;
		else
			temp->next=val;

		item->value = temp;  
		item->key = a[i][c]%97;

		ht[hashIndex]=item;
		c++;
	}
}
void print(struct hash *ht[])
{
	for(int i=0;i<26;i++)
	{
		if(ht[i]->value!=NULL)
		{
			printf("%c ",(char)ht[i]->key+97);
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

}
