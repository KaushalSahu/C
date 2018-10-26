#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node {
	int data;
	struct Node* next; 
	struct Node* prev; 
};

void append(struct Node** head_ref, int new_data)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

	struct Node* last = *head_ref; 

	new_node->data = new_data;

	new_node->next = NULL;

	if (*head_ref == NULL) {
		new_node->prev = NULL;
		*head_ref = new_node;
		return;
	}

	while (last->next != NULL)
		last = last->next;

	last->next = new_node;

	new_node->prev = last;

	return;
}

void deleteNode(struct Node **head_ref, struct Node *del)
{
	if(*head_ref == NULL || del == NULL)
		return;

	if(*head_ref == del)
		*head_ref = del->next;

	if(del->next != NULL)
		del->next->prev = del->prev;

	if(del->prev != NULL)
		del->prev->next = del->next;

	free(del);
	return;
}


bool search(struct Node* head, int x)
{
	struct Node* current = head;  
	while (current != NULL)
	{
		if (current->data == x)
			return true;
		current = current->next;
	}
	return false;
}

void printList(struct Node* node)
{
	struct Node* last;
	printf("\nTraversal in forward direction \n");
	while (node != NULL) {
		printf(" %d ", node->data);
		last = node;
		node = node->next;
	}

	printf("\nTraversal in reverse direction \n");
	while (last != NULL) {
		printf(" %d ", last->data);
		last = last->prev;
	}
}

int main()
{
	struct Node* head = NULL;

	int num;
	FILE *fptr;

	if ((fptr = fopen("/home/kaushal/Desktop/program.txt","r")) == NULL){
		printf("Error! opening file");

		exit(1);
	}

	int c;
	while(fscanf(fptr,"%d", &num)==1 )
	{
		append(&head,num);
	}


	printf("Created DLL is: ");
	printList(head);

	search(head, 21)? printf("\nElement Found.") : printf("\nElement Not Found!!!");

	struct Node *curr = head;

	while(curr!=NULL && curr->next!=NULL)
		curr=curr->next;

	if(curr!=NULL)
		deleteNode(&head,curr);

	printList(head);


	printf("\n");
	return 0;
}
