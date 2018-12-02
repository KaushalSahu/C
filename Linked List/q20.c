#include <stdio.h>
#include <stdlib.h>

struct node 
{
	int data;
	struct node *next;
};

struct node * newNode(int data)
{
	struct node *temp = (struct node *) malloc(sizeof(struct node));
	temp->data = data;
	temp->next = NULL;

	return temp;
}

struct node * insert(struct node *root, int data)
{
	struct node *curr;

	if(root == NULL) {
		return newNode(data);
	}

	curr = root;

	while(curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = newNode(data);

	return root;
}

void frequency(struct node *start) 
{ 
	struct node *ptr1;
	struct node *ptr2;
	struct node *dup; 
	int count;

	ptr1 = start; 

	while (ptr1 != NULL) { 
		ptr2 = ptr1;
		count = 1;

		while (ptr2->next != NULL) {

			if (ptr1->data == ptr2->next->data) { 			

				count++;
				dup = ptr2->next; 
				ptr2->next = ptr2->next->next; 
				free(dup);
				dup = NULL;
			} else {
				ptr2 = ptr2->next; 
			}
		}
		printf("Freq(%d) = %d\n", ptr1->data, count);
		ptr1 = ptr1->next; 
	} 
} 

int main()
{
	int n;
	int i;
	int x;
	struct node *root;

	root = NULL;
	scanf("%d", &n);

	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		root = insert(root, x);
	}
	frequency(root);

	return 0;
}
