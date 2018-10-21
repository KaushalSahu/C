#include<stdio.h>
#include<stdlib.h>
struct node 
{
	int data;
	struct node *next;
};
struct node *newNode(int data)
{
	struct node *temp =  (struct node *)malloc(sizeof(struct node));
	temp->data =data;
	temp->next =NULL;
	return temp;
}
struct node *insert(struct node *root,int data)
{
	struct node *curr = root;
	if(curr==NULL)
		return newNode(data);
	while(curr->next!=NULL)
		curr = curr->next;
	curr->next = newNode(data);
	return root;
}
struct node *remov(struct node *root)
{
	struct node *curr = root;
	struct node *prev = NULL;
	while(curr->next != NULL)
	{
		if(curr->data < curr->next->data)
		{
			struct node *temp = curr;
			if(curr == root)
			{
				root = curr->next;
				prev = curr->next;
			}
			else	
			{
				prev->next = curr->next;
			}
			curr = curr->next;
			free(temp);
			temp = NULL;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return root;
}
void print(struct node *root)
{
	while(root!=NULL)
	{
		printf("%d ",root->data);
		root = root->next;
	}
}
int main()
{
	int i;
	int n;
	int a;
	int k;
	struct node *root = NULL;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a);
		root = insert(root,a);
	}
	root = remov(root);
	print(root);
}
