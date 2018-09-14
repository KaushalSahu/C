#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 357

struct node{
	char *x;
	char *y;
	struct node *next;
};

struct hash{
	struct node *key[MAX];
};

void init(struct hash *h)
{
	int i;
	for (i = 0; i < MAX; ++i) {
		h->key[i] = NULL;
	}

	return;
}

void str_copy(char **target, char *source, int len)
{
	int i;

	*target = (char*)malloc(len * sizeof(char));

	for (i = 0; i < len; ++i) {
		*((*target) + i) = source[i];
	}

	return;
}

struct node* alloc(char *x, char *y)
{
	struct node *tmp;
	tmp = (struct node*)malloc(sizeof(struct node));
	str_copy(&tmp->x, x, strlen(x));
	str_copy(&tmp->y, y, strlen(y));
	tmp->next = NULL;

	return tmp;
}


/* Using djb2 hashing algorithm to hash both strings */
unsigned int hash_func(char *x, char *y)
{
	unsigned int h;
	int i;
	int len;

	h = 5381;
	len = strlen(x);

	for (i = 0; i < len; ++i) {
		h = ((h << 5) + h) + x[i];
	}

	len = strlen(y);

	for (i = 0; i < len; ++i) {
		h = ((h<<5) + h) + y[i];
	}

	return (h % MAX);
}

/* This function inserts directly without checking if key has same values. Check it before using this function. */
void insert_into_hash(struct hash *h, char *x, char *y)
{
	unsigned int hash_index;
	struct node *curr;

	hash_index = hash_func(x, y);

	if (h->key[hash_index] == NULL) {
		h->key[hash_index] = alloc(x, y);
	} else {
		curr = h->key[hash_index];
		/* find last element in list */
		while (curr->next != NULL) {
			curr = curr->next;
		}
		/* and insert */
		curr->next = alloc(x, y);
	}

	return;
}

int main()
{
	int n;
	int i;
	int count;
	unsigned int hash_index;
	char x[20][256];
	struct hash h;

	init(&h);

	scanf("%d", &n);

	for (i = 0; i < n; ++i) {
		scanf("%255s", x[i]);
	}
	count = 0;
	for (i = 1; i < n; ++i) {
		hash_index = hash_func(x[i-1], x[i]);
		if (h.key[hash_index] == NULL) {
			insert_into_hash(&h, x[i-1], x[i]);
			++count;
		} else {
			if ((strcmp(h.key[hash_index]->x, x[i-1]) == 0) && (strcmp(h.key[hash_index]->y, x[i]) == 0)) {
				continue;
			} else {
				insert_into_hash(&h, x[i-1], x[i]);
				++count;
			}
		}
	}

	printf("%d\n", count);

	return 0;
}
