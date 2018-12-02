#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node 
{
	char data;
	struct node *next;
};

struct node * newNode(char data)
{
	struct node *temp = (struct node *) malloc(sizeof(struct node));
	temp->data = data;
	temp->next = NULL;

	return temp;
}

struct node * insert(struct node *root, char data)
{
	struct node *curr = root;
	if(curr == NULL) {
		return newNode(data);
	}

	while(curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = newNode(data);

	return root;
}

struct node * reverse (struct node *head) 
{
	if(head->next == NULL) {
		return head;
	} else {
		struct node *newhead = reverse(head->next);
		head->next->next = head;
		head->next = NULL;

		return newhead;
	}
}

void palindrome(struct node *root1, struct node *root2)
{
	while(root1 != NULL && root2 != NULL && root1->data == root2->data) {

		root1 = root1->next;
		root2 = root2->next;
	}
	if(root1 == NULL && root2 == NULL) {
		printf("palindrome");
	}
	else {
		printf("not palindrome");
	}
}

void print(struct node *root)
{
	while(root != NULL) {
		printf("%c ", root->data);
		root = root->next;
	}
}

int main()
{
	int i;
	int n;
	char a;

	struct node *root = NULL;
	struct node *root1 = NULL;
	struct node *root2 = NULL;

	scanf("%d",&n);

	for(i = 0; i < n; i++) {
		scanf(" %c", &a);
		root = insert(root, a);
		root1 = insert(root1, a);
	}

	root2 = reverse(root1);

	palindrome(root, root2);

	return 0;
}
