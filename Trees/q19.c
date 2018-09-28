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
void level(struct node* root,int lev)
{
    if (root == NULL)
       return;
     level(root->left, lev+1);
     printf("%d %d \n",root->key,lev);
     level(root->right, lev+1);
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
	level(root,0);

}
