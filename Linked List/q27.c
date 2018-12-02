#include <stdio.h>
#include <stdlib.h>

struct node 
{
	int data;
	int next;
};

void malloc_arr(struct node *ele, int data)
{
	ele->data = data;
}

void free_arr(struct node root[], int n, int data)
{
	int i;

	for(i = 0; i < n; i++) {
		if(root[i].data == data) {
			if(i != 0) {
				root[i-1].next = i+1;
			}
			else {
				root[i].data = -99999;
			}
		}
	}
}

void print(int n,struct node root[]) 
{
	int i;
	for(i = 0; i < n; i = root[i].next) {
		if(root[i].data != -99999)
			printf("%d ", root[i].data);
	}
}

int main()
{
	int n;
	int i;
	int x;

	scanf("%d", &n);

	struct node root[n];

	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		malloc_arr(&root[i], x);
		root[i].next = i+1;
	}
	print(n, root);

	printf("\nEnter the element to remove : ");
	scanf("%d", &x);

	free_arr(root, n, x);
	print(n, root);

	return 0;
}
