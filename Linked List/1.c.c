
#include<stdlib.h>

struct node
{
	int data;
	struct node *next;
};

struct node * s;

void push()
{
	struct node *temp, *curr;
	int n;
	temp = (struct node*)malloc(sizeof(struct node));
	scanf("%d",&n);
	scanf("%d",&temp->data);
	curr=s;
	if(curr!=NULL)
	{
	while(curr->data!=n)
		curr=curr->next;
	temp->next=curr->next;
	curr->next=temp;
	}
}
void printm()
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp =s;
	while(temp!=NULL)
	{
		printf("%d -> ",temp->data);
		temp=temp->next;
	}
	printf("done");
}
int main()
{
	s = (struct node*)malloc(sizeof(struct node));
	s=NULL;
	int c;
	while(1)
	{
		printf("Enter 1 for insert 2 for print and 3 for exit: ");
		scanf("%d",&c);
		if(c==1)
			push();
		else if(c==2)
			printm();
		else if(c==3)
			break;
	}
	return 0;
}






























































