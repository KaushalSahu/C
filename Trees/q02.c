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
void preorder(struct node *root)
{
	if(root!=NULL)
	{
		printf("%d_",root->key);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(struct node *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d_", root->key);
		inorder(root->right);
	}

}
void postorder(struct node *root)
{
	if (root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d_", root->key);
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
	preorder(root);
	printf("\n");
	inorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
	return 0;
}
