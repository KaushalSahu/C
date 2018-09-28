#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
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
bool printAncestors(struct node *root, int target)
{
	if (root == NULL)
		return false;

	if (root->key == target)
		return true;

	if ( printAncestors(root->left, target) || printAncestors(root->right, target) )
	{
		printf("%d ",root->key);
		return true;
	}
	return false;
}
int main()
{
	int n;
	int i;
	int a;
	int k;
	struct node *root = NULL;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a);
		root = insert(root,a);
	}
	scanf("%d",&k);
	printAncestors(root, k);
	return 0;
}
