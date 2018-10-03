#include<stdio.h> 
#include<stdlib.h>
#include<stdbool.h>
#define MAX_Q_SIZE 500
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

struct node** createQueue(int *, int *); 
void enQueue(struct node **, int *, struct node *); 
struct node *deQueue(struct node **, int *); 

void printLevelOrder(struct node* root) 
{ 
	int rear, front; 
	struct node **queue = createQueue(&front, &rear); 
	struct node *temp_node = root; 

	while (temp_node) 
	{ 
		printf("%d ", temp_node->data); 

		if (temp_node->left) 
			enQueue(queue, &rear, temp_node->left); 

		if (temp_node->right) 
			enQueue(queue, &rear, temp_node->right); 

		temp_node = deQueue(queue, &front); 
	} 
} 

struct node** createQueue(int *front, int *rear) 
{ 
	struct node **queue = (struct node **)malloc(sizeof(struct node*)*MAX_Q_SIZE); 

	*front = *rear = 0; 
	return queue; 
} 

void enQueue(struct node **queue, int *rear, struct node *new_node) 
{ 
	queue[*rear] = new_node; 
	(*rear)++; 
} 

struct node *deQueue(struct node **queue, int *front) 
{ 
	(*front)++; 
	return queue[*front - 1]; 
}
int main() 
{ 
	int n;
	scanf("%d",&n);
	int arr[n];
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	struct node* root = insertLevelOrder(arr, root, 0, n); 
	printLevelOrder(root);
}
