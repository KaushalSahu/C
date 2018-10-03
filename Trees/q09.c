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
void deleteTree(struct node* node)
{
	if (node == NULL) 
		return;

	deleteTree(node->left);
	deleteTree(node->right);

	printf("\nDeleting:%d", node->key);
	free(node);
}
void deletebinaryTree(struct node** node_ref)
{
	deleteTree(*node_ref);
	*node_ref = NULL;
}
int main()
{
	int n;
	int i;
	int a;
	scanf("%d",&n);
	struct node *root = NULL;
	for(i=0;i<n;i++)
	{
		scanf("%d",&a);
		root = insert(root,a);
	}
	deletebinaryTree(&root);
	return 0;
}
