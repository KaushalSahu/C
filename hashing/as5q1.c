#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *friend;
	struct node *next;
};
struct hash
{
	struct node *key;
	struct node *value;
};

struct node* create(struct node *head, int a)
{
	struct node* curr;
	struct node* temp=(struct node*)malloc(sizeof(struct node));
	temp->data=a;
	temp->next=NULL;
	temp->friend=NULL;
	curr=head;

	if(head==NULL)
		head=temp;
	else
	{
		while(curr->next!=NULL)
			curr=curr->next;
		curr->next=temp;
	}
	return head;
}
void print(struct hash *ht[],int n)
{
	/*struct node *temp=(struct node*)malloc(sizeof(struct node));
	temp=head;
	while(temp!=NULL)
	{
	printf("%d_",temp->friend->data);
	temp=temp->next;
	}*/
	int i=-1;
	while(++i<n)	
		printf("%d_",ht[i]->value->data);
}


int main()
{

	int n;
	int a;
	int b;
	int c;

	struct node *head=(struct node*)malloc(sizeof(struct node));
	head=NULL;

	scanf("%d",&n);
	struct hash *ht[n];
	int arr[n];

	for(int i=0;i<n;i++)
	{
		scanf("%d",&a);
		scanf("%d",&arr[i]);
		head=create(head,a);
	}
	struct node *temp=(struct node*)malloc(sizeof(struct node));
	struct node *curr=(struct node*)malloc(sizeof(struct node));
	temp=head;
	for(int i=0;i<n;i++)
	{
		curr=head;
		c=1;
		while(c!=arr[i]&&curr!=NULL)
		{
			curr=curr->next;
			c++;
		}
		temp->friend=curr;
		struct hash *item=(struct hash*)malloc(sizeof(struct hash));
		item->key=temp;
		item->value=temp->friend;
		ht[i]=item;
		temp=temp->next;
	}
	print(ht,n);
	return 0;
}
