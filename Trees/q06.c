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

void leafsum(struct node *root, int *sum){ 
    if (!root) 
        return; 
  
    leafsum(root->left, sum); 
    if (!root->left && !root->right) 
        *sum += root->key; 
  
    leafsum(root->right, sum); 
} 

int main()
{
	int n;
	int i;
	int a;
	int sum = 0;
	scanf("%d",&n);
	struct node *root = NULL;
	for(i=0;i<n;i++)
	{
		scanf("%d",&a);
		root = insert(root,a);
	}
	leafsum(root,&sum);
	printf("%d",sum);
	return 0;
}
