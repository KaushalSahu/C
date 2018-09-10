#include<stdio.h>
#include<stdlib.h>
 
struct Node
{
    int data;
    struct Node* next;
};
 

void sortedInsert(struct Node**, struct Node*);

void insertionSort(struct Node **head_ref)
{
    struct Node *sorted = NULL;
 
    struct Node *cur = *head_ref;
    while (cur != NULL)
    {
        struct Node *next = cur->next;
 
        sortedInsert(&sorted, cur);
 
        cur = next;
    }
    *head_ref = sorted;
}
 
void sortedInsert(struct Node** head_ref, struct Node* new_node)
{
    struct Node* cur;
    if (*head_ref == NULL || (*head_ref)->data >= new_node->data)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        cur = *head_ref;
        while (cur->next!=NULL && cur->next->data < new_node->data)
        {
            cur = cur->next;
        }
        new_node->next = cur->next;
        cur->next = new_node;
    }
}
 
 
void printList(struct Node *head)
{
    struct Node *temp = head;
    while(temp != NULL)
    {
        printf("%d  ", temp->data);
        temp = temp->next;
    }
}
 
void push(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
 
    new_node->data  = new_data;
 
    new_node->next = (*head_ref);
 
    (*head_ref)    = new_node;
}
 
 
int main()
{
    int val;
    int n;
    struct Node *a = NULL;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
	    scanf("%d",&val);
    push(&a,val);
    }

    printf("Linked List before sorting \n");
    printList(a);
 
    insertionSort(&a);
 
    printf("\nLinked List after sorting \n");
    printList(a);
 
    return 0;
}

