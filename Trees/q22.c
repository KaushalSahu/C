#include<stdio.h> 
#include<stdlib.h>
struct node 
{ 
	int data; 
	struct node* left, * right; 
}; 
struct node* newNode(int data) 
{ 
	struct node* node = (struct node*)malloc(sizeof(node)); 
	node->data = data; 
	node->left = node->right = NULL; 
	return (node); 
} 
struct node* insertLevelOrder(int arr[], struct node* root,int i, int n) 
{ 
	if (i < n) 
	{ 
		struct node* temp = newNode(arr[i]); 
		root = temp; 

		root->left = insertLevelOrder(arr,root->left, 2 * i + 1, n); 

		root->right = insertLevelOrder(arr,root->right, 2 * i + 2, n); 
	} 
	return root; 
}

void inorder(struct node *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d ",root->data);
		inorder(root->right);
	}
}
struct node *prune(struct node *root, int sum) 
{ 
	if (root == NULL) return NULL; 

	root->left = prune(root->left, sum - root->data); 
	root->right = prune(root->right, sum - root->data); 

	if (root->left==NULL && root->right==NULL) 
	{ 
		if (root->data < sum) 
		{ 
			free(root); 
			return NULL; 
		} 
	} 
	return root; 
} 
int main() 
{ 
	int n;
	int sum;
	scanf("%d",&n);
	int arr[n];
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	struct node* root = insertLevelOrder(arr, root, 0, n); 
	scanf("%d",&sum);
	root = prune(root,sum);
	inorder(root);
	return 0;
}
