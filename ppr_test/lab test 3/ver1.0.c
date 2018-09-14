#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 97

struct node {
	char key[11];
	char value[11];
	struct node *next;
};

int hash(char s[]) 
{
	int k;
	int i;
	k = 0;

	for (i = 0; s[i] != '\0' ; ++i) {
		k += s[i];
	}

	k = k % SIZE;
	return k;
}

int search(struct node *table[], char w1[], char w2[]) 
{
	struct node *temp = NULL;
	int k;

	k = hash(w1);
	
	for (temp = table[k]; temp != NULL; temp = temp->next) {
		if ((strcmp(temp->key, w1) == 0) && 
				(strcmp(temp->value, w2) == 0))
			return 1;
	}
	return 0;
}

void insert(struct node *table[], char w1[], char w2[]) 
{
	struct node *temp = NULL;
	int k;

	k = hash(w1);
	temp = (struct node *) malloc(sizeof(struct node));
	
	strcpy(temp->key, w1);
	strcpy(temp->value, w2);
	temp->next = NULL;
	if (table[k] == NULL) {
		table[k] = temp;
		return;
	}
	temp->next = table[k];
	table[k] = temp;

}

int main()
{
	struct node *table[SIZE] = {NULL};
	char words[20][11];
	int n;
	int i;
	int count;
	int found;

	count = 0;
	scanf("%d", &n);

	for (i = 0; i < n; ++i) {
		scanf("%s", words[i]);
		found = 0;
		if (i > 0) {
			found = search(table, words[i - 1], words[i]);
			if (found == 0) {
				insert(table, words[i - 1], words[i]);
				++count;
			}
		}
	}

	printf("%d\n", count);	

	return 0;
}
