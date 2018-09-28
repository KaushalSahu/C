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

struct node* LCA(struct node * root, int n1,int n2) 
{ 
    // Your code here 
    if (root == NULL) 
       return root; 
    if (root->data == n1 || root->data == n2) 
       return root; 
  
    struct node* left = LCA(root->left, n1, n2); 
    struct node* right = LCA(root->right, n1, n2); 
  
    if (left != NULL && right != NULL) 
         return root; 
    if (left != NULL) 
        return LCA(root->left, n1, n2); 
  
    return LCA(root->right, n1, n2); 
} 
  
// Returns level of data k if it is present in 
// tree, otherwise returns -1 
int findLevel(struct node *root, int k, int level) 
{ 
    if(root == NULL) return -1; 
    if(root->data == k) return level; 
  
    int left = findLevel(root->left, k, level+1); 
    if (left == -1) 
       return findLevel(root->right, k, level+1); 
    return left; 
} 
  
int findDistance(struct node* root, int a, int b) 
{ 
    // Your code here 
    struct node* lca = LCA(root, a , b); 
  
    int d1 = findLevel(lca, a, 0); 
    int d2 = findLevel(lca, b, 0); 
  
    return d1 + d2; 
} 
int main() 
{ 
	int n;
	int a;
	int b;

	scanf("%d",&n);
	int arr[n];
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	struct node* root = insertLevelOrder(arr, root, 0, n); 
	scanf("%d",&a);
	scanf("%d",&b);
	printf("%d",findDistance(root,a,b));

}
