#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *left;
	struct node *right;	
};
struct node* search(struct node* root, int key)
{
	if (root == NULL || root->data == key)
		return root;

	if (root->data < key)
		return search(root->right, key);

	return search(root->left, key);
}
int main()
{
	int n , i, k, a;
	struct node *p , *q , *root;
	scanf("%d",&n);	
	for(i=0;i<n;i++)
	{
		p = (struct node*)malloc(sizeof(struct node));
		scanf("%d",&p->data);
		p->left = NULL;
		p->right = NULL;
		if(i == 0)
		{
			root = p; 
		}
		else
		{	
			q = root;   
			while(1)
			{				
				if(p->data > q->data)
				{
					if(q->right == NULL)
					{					
						q->right = p;
						break;
					}
					else
						q = q->right;
				}
				else
				{
					if(q->left == NULL)
					{						
						q->left = p;
						break;
					}
					else
						q = q->left;										
				}				
			}

		}

	}
	scanf("%d",&k);
	for(i=0;i<k;i++)
	{
		scanf("%d",&a);
		struct node *temp = search(root,a);
		if(temp !=NULL && temp->data == a)
			printf("y");
		else 
			printf("n");
		printf("\n");
	}
	return 0;
}
