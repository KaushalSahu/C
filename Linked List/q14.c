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
struct node *reverse (struct node *root, int k) 
{ 
	struct node* current = root; 
	struct node* next = NULL; 
	struct node* prev = NULL; 
	int count = 0;    

	while (current != NULL && count < k) 
	{ 
		next  = current->next; 
		current->next = prev; 
		prev = current; 
		current = next; 
		count++; 
	} 

	if (next !=  NULL) 
		root->next = reverse(next, k);  

	return prev; 
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
	scanf("%d",&k);
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a);
		root = insert(root,a);
	}
	root = reverse(root,k);
	print(root);
}
