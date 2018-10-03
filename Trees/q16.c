#include<stdio.h> 
#include<stdlib.h>
#include<stdbool.h>
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

bool isBST(struct node* root, struct node* l, struct node* r) 
{ 
	if (root == NULL) 
		return true; 

	if (l != NULL && root->data < l->data) 
		return false; 

	if (r != NULL && root->data > r->data) 
		return false; 

	return isBST(root->left, l, root) && isBST(root->right, root, r); 
} 
int main() 
{ 
	int n;
	scanf("%d",&n);
	int arr[n];
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	struct node* root = insertLevelOrder(arr, root, 0, n); 

	if (isBST(root,NULL,NULL))
		printf("Is BST");
	else
		printf("Not a BST");
}
