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
void print(int a[],int l)
{
	int i;
	for(i=0;i<l;i++)
		printf("%d ",a[i]);
	printf("\n");
}

void rootleaf(struct node*root, int l, int a[])
{
	if(root==NULL)
		return;
	a[l]=root->key;
	rootleaf(root->left,l+1,a);
	rootleaf(root->right,l+1,a);
	if(root->left==NULL && root->right==NULL)
		print(a,l+1);

}

int main()
{
	int n;
	int i;
	int a;
	scanf("%d",&n);
	int arr[n];
	struct node *root = NULL;
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
		root = insert(root,arr[i]);
	}
	rootleaf(root,0,arr);
}
