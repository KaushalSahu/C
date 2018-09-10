#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/* Node of a doubly linked list */
struct Node {
	int data;
	struct Node* next; // Pointer to next node in DLL
	struct Node* prev; // Pointer to previous node in DLL
};

void append(struct Node** head_ref, int new_data)
{
	/* 1. allocate node */
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

	struct Node* last = *head_ref; /* used in step 5*/

	/* 2. put in the data  */
	new_node->data = new_data;

	/* 3. This new node is going to be the last node, so
	   make next of it as NULL*/
	new_node->next = NULL;

	/* 4. If the Linked List is empty, then make the new
	   node as head */
	if (*head_ref == NULL) {
		new_node->prev = NULL;
		*head_ref = new_node;
		return;
	}

	/* 5. Else traverse till the last node */
	while (last->next != NULL)
		last = last->next;

	/* 6. Change the next of last node */
	last->next = new_node;

	/* 7. Make last node as previous of new node */
	new_node->prev = last;

	return;
}

void deleteNode(struct Node **head_ref, struct Node *del)
{
  /* base case */
  if(*head_ref == NULL || del == NULL)
    return;

  /* If node to be deleted is head node */
  if(*head_ref == del)
    *head_ref = del->next;

  /* Change next only if node to be deleted is NOT the last node */
  if(del->next != NULL)
    del->next->prev = del->prev;

  /* Change prev only if node to be deleted is NOT the first node */
  if(del->prev != NULL)
    del->prev->next = del->next;

  /* Finally, free the memory occupied by del*/
  free(del);
  return;
}


/* Checks whether the value x is present in linked list */
bool search(struct Node* head, int x)
{
    struct Node* current = head;  // Initialize current
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

/* Driver program to test above functions*/
int main()
{
	/* Start with the empty list */
	struct Node* head = NULL;

	int num;
	FILE *fptr;

	if ((fptr = fopen("/home/kaushal/Desktop/program.txt","r")) == NULL){
		printf("Error! opening file");

		// Program exits if the file pointer returns NULL.
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
