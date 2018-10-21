#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *next;
};
struct node *newNode(int data)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->data = data;
	temp->next = NULL;
	return temp;
}
struct node *insert(struct node *root,int data)
{
	if(root == NULL)
		return newNode(data);

	struct node *curr = root;

	while(curr->next!=NULL)
		curr = curr->next;
	curr->next = newNode(data);

	return root;
}
void print(struct node *root,int k)
{
	struct node*tmp=root,*h=NULL;
	int count=0;
	while(1)
	{
		if(count%k == 0)
		{
			if(h==root)
				break;
			printf("%d -> ",tmp->data);
		}
		count++;
		tmp=tmp->next;
		h=tmp;
	}
	puts("NULL");
}
int main()
{
	int a;
	int i;
	int n;
	int k;
	struct node *root;
	root = NULL;
	scanf("%d",&k);
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a);
		root = insert(root,a);
	}
	struct node *curr = root;
	while(curr->next != NULL)
		curr = curr->next;
	curr->next = root;
	//ptr(root);
	print(root,k);
	return 0;
}
