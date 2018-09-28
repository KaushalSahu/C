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
void findPreSuc(struct node* root, struct node **pre, struct node **suc, int key)
{
	if (root == NULL)  
		return ;

	if (root->key == key)
	{
		if (root->left != NULL)
		{
			struct node* tmp = root->left;
			while (tmp->right)
				tmp = tmp->right;
			*pre = tmp ;
		}

		if (root->right != NULL)
		{
			struct node* tmp = root->right ;
			while (tmp->left)
				tmp = tmp->left ;
			*suc = tmp ;
		}
		return ;
	}

	if (root->key > key)
	{
		*suc = root ;
		findPreSuc(root->left, pre, suc, key) ;
	}
	else 
	{
		*pre = root ;
		findPreSuc(root->right, pre, suc, key) ;
	}
}
int main()
{
	int n;
	int i;
	int a;
	int k;
	struct node *root = NULL;
	struct node *pre = NULL, *suc = NULL;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a);
		root = insert(root,a);
	}
	scanf("%d",&k);
	findPreSuc(root, &pre, &suc, k);
	if(pre!=NULL)
		printf("%d ",pre->key);
	if(suc!=NULL)
		printf("%d ",suc->key);
	return 0;
}
