#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *next;
};

struct node *s;

void push()
{   
	struct node *temp, *cur;
	temp = (struct  node *) malloc(sizeof(struct node));
	scanf("%d", &temp->data);
	temp->next = NULL;
	cur = s;

	if(s == NULL) {
		s = temp;
	} else {
		while(cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = temp;
	}
	printf("done \n");
}

void printm()
{   
	struct node * temp = s;

	while(temp != NULL) {
		printf("%d -> ", temp->data);
		temp = temp->next;
	}
	printf("DONE\n");
}

int main()
{
	s = (struct node *) malloc(sizeof(struct node));
	s = NULL;
	int h;

	while(1) {
		printf("\n1 to push \n2 to print \n0 to exit : ");
		scanf("%d",&h);
		if(h == 1) {
			push();
		}
		if(h == 2) {
			printm();
		}
		if(h == 0) {
			break;
		}
	}

	return 0;
}
