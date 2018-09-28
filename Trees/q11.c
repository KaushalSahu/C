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
void printkdistant(struct node *root , int k)
{
	if(root == NULL)
		return;
	if( k == 0 )
	{
		printf( "%d ", root->key );
		return ;
	}
	else
	{
		printkdistant( root->left, k-1 ) ;
		printkdistant( root->right, k-1 ) ;
	}
}
int main()
{
	int n;
	int i;
	int a;
	int k;
	scanf("%d",&n);
	struct node *root = NULL;
	for(i=0;i<n;i++)
	{
		scanf("%d",&a);
		root = insert(root,a);
	}
	scanf("%d",&k);
	printkdistant(root, k);
	return 0;
}
