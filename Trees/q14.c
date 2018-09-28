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
struct node* leafDelete(struct node *root)
{
	if(root == NULL)
		return NULL;
	if (root->left == NULL && root->right == NULL) 
	{
		free(root);
		return NULL;
	}

	root->left = leafDelete(root->left);
	root->right = leafDelete(root->right);

	return root;
}
void inorder(struct node* root)
{
	if (root != NULL) 
	{
		inorder(root->left);
		printf("%d ",root->key);
		inorder(root->right);
	}
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
	leafDelete(root);
	inorder(root);
	return 0;
}
