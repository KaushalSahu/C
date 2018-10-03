#include<stdio.h>
#include<stdlib.h>
struct node
{
	int key;
	struct node *left, *right;
};
struct node *newNode(int item)
{
	struct node *temp =(struct node *)malloc(sizeof(struct node));
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
void inOrder(struct node *root)
{
	if(root!=NULL)
	{
		struct node *temp;
		if(root->left!=NULL)
		{
			if(root->key == root->left->key)
			{
				if(root->left->left!=NULL)
				{
					temp = root->left;
					root->left=root->left->left;
					free(temp);
					temp = NULL;
				}
				else if(root->left->right!=NULL)
				{
					temp = root->left;
					root->left=root->left->right;
					free(temp);
					temp = NULL;
				}
				else
					root->left = NULL;
			}
		}
		inOrder(root->left);
		inOrder(root->right);
	}
}
void print(struct node *root)
{
	if(root!=NULL)
	{
		print(root->left);
		printf("%d ",root->key);
		print(root->right);
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
	inOrder(root);
	print(root);
	return 0;
}
