#include<stdio.h>
#include<stdlib.h>
struct node
{
	int key;
	struct node *left, *right;
};
struct node *newNode(int item)
{
	struct node *temp =  (struct node *)malloc(sizeof(struct node));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}
struct node* insert(struct node* node, int key)
{
	if (node == NULL) 
		return newNode(key);

	if (key <= node->key)
		node->left  = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);   

	return node;
}
int identical(struct node* a, struct node* b) 
{ 
	if (a==NULL && b==NULL) 
		return 1; 

	if (a!=NULL && b!=NULL) 
	{ 
		return(a->key == b->key && identical(a->left, b->left) && identical(a->right, b->right)); 
	} 
	return 0; 
}  
int main()
{
	int n;
	int i;
	int a;
	int t;
	scanf("%d",&t);
	scanf("%d",&n);
	while(t--)
	{
		struct node *root1 = NULL;
		struct node *root2 = NULL;
		for(i=0;i<n;i++)
		{
			scanf("%d",&a);
			root1 = insert(root1,a);
		}
		for(i=0;i<n;i++)
		{
			scanf("%d",&a);
			root2 = insert(root2,a);
		}
		if(identical(root1,root2))
			printf("y");
		else
			printf("n");
	}
	return 0;
}
