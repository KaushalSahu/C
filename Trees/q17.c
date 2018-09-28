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

int sum(struct node *root)
{
   if(root == NULL)
     return 0;
   return sum(root->left) + root->data + sum(root->right);
}

int isSumTree(struct node* node) 
{ 
	int ls, rs; 

	if(node == NULL || (node->left == NULL && node->right == NULL)) 
		return 1; 

	ls = sum(node->left); 
	rs = sum(node->right); 

	if((node->data == ls + rs)&& isSumTree(node->left) && isSumTree(node->right)) 
		return 1; 

	return 0; 
} 

int main() 
{ 
	int n;
	scanf("%d",&n);
	int arr[n];
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	struct node* root = insertLevelOrder(arr, root, 0, n); 
	if(isSumTree(root)==1)
		printf("1");
	else
		printf("0");
	}
