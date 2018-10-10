#include<stdio.h>
#include<stdlib.h>

struct node 
{
	int data;
	struct node *left,*right;
};
struct node *newNode(int data)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
struct node  *insert(struct node *root,int x)
{
	if(root == NULL)
		return newNode(x);
	if(x<root->data)
		root->left = insert(root->left,x);
	if(x>root->data)
		root->right = insert(root->right,x);

	return root;
}
void inorder(struct node *root)
{
	if(root!=NULL)
	{
		inorder(root->left);
		printf("%d ",root->data);
		inorder(root->right);
	}
}
void preorder(struct node *root)
{
	if(root!=NULL)
	{
		printf("%d ",root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
struct node *leftrotate(struct node *root)
{
	struct node *temp;
	struct node *temp2 = root->right;
	if(root!=NULL)
	{
		if(root->left!=NULL && root->right!=NULL)
		{
			if(root->right->left != NULL)
				temp = root->right->left;
			root->right->left = root;
			root->right = temp;
		}
	}
	return temp2;
}
int main()
{
	int i;
	int n;
	int x;
	struct node *root = NULL;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&x);
		root = insert(root,x);
	}
	inorder(root);
	printf("\n");
	root = leftrotate(root);
	preorder(root);
	printf("\n");
	return 0;
}
