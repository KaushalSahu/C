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
void mirror(struct node* node)
{
	if (node==NULL)
		return;
	else
	{
		struct node* temp;

		mirror(node->left);
		mirror(node->right);

		temp        = node->left;
		node->left  = node->right;
		node->right = temp;
	}
}
void inorder(struct node* node)
{
  if (node == NULL)
    return;

  inorder(node->left);
  printf("%d ", node->key);
  inorder(node->right);
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
	mirror(root);
	inorder(root);
	return 0;
}
