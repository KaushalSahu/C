#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3 //maximum children
#define MIN 2 //minimum children

int num = 0;

struct node {
	int count;
	int offset[MAX+1];
	char word[MAX+1][26];
	struct node *link[MAX+1];
};

struct meaning {
	char mean[26];
};

struct node *root = NULL;

struct node * createNode(char word[], char mean[], struct node *child) {
	struct node *newNode;
	struct meaning m;
	FILE *fp;

	newNode = (struct node *) malloc(sizeof(struct node));

	strcpy(newNode->word[1],word);
	newNode->count = 1;
	newNode->link[0] = root;
	newNode->link[1] = child;
	newNode->offset[1] = num++;

	fp = fopen("meanings.txt", "a+");

	if (fp == NULL) {
		printf("meanings file not found\n");
		return NULL;
	}

	strcpy(m.mean, mean);
	fwrite(&m, sizeof(struct meaning), 1, fp);
	fclose(fp);

	return newNode;
}

/* Places the wordue in appropriate position */
void addValToNode(char word[],char mean[], int pos, struct node *node, struct node *child) {
	FILE *fp;
	struct meaning m;
	int j;

	j = node->count;

	while (j > pos) {
		strcpy(node->word[j + 1], node->word[j]);
		node->link[j + 1] = node->link[j];
		node->offset[j+1] = node->offset[j];
		j--;
	}

	strcpy(node->word[j + 1], word);
	node->link[j + 1] = child;
	node->count++;
	node->offset[j+1] = num++;

	fp = fopen("meanings.txt", "a+");

	if (fp == NULL) {
		printf("meanings file not found\n");
	}

	strcpy(m.mean, mean);
	fwrite(&m, sizeof(struct meaning), 1, fp);
	fclose(fp);
}

/* split the node */
void splitNode (char word[], char mean[], char **pword, int pos, struct node *node, struct node *child, struct node **newNode) {
	int median;
	int j;

	if (pos > MIN)
		median = MIN + 1;
	else
		median = MIN;

	*newNode = (struct node *) malloc(sizeof(struct node));
	j = median + 1;

	while (j <= MAX) {
		strcpy((*newNode)->word[j - median], node->word[j]);
		(*newNode)->link[j - median] = node->link[j];
		j++;
	}

	node->count = median;
	(*newNode)->count = MAX - median;

	if (pos <= MIN) {
		addValToNode(word,mean, pos, node, child);
	} else {
		addValToNode(word,mean, pos - median, *newNode, child);
	}

	strcpy(*pword, node->word[node->count]);
	(*newNode)->link[0] = node->link[node->count];
	node->count--;
}

/* sets the value val in the node */
int setValueInNode(char word[], char mean[], char **pval, struct node *node, struct node **child) {
	int pos;

	if (node == NULL) {
		*pval = word;
		*child = NULL;

		return 1;
	}

	if (strcmp(word, node->word[1]) < 0) {
		pos = 0;
	} else {
		for (pos = node->count; (strcmp(word, node->word[pos]) < 0 && pos > 1); pos--);
		if (strcmp(word, node->word[pos]) == 0) {
			printf("Duplicates not allowed\n");

			return 0;
		}
	}
	if (setValueInNode(word, mean, pval, node->link[pos], child)) {
		if (node->count < MAX) {
			addValToNode(*pval, mean, pos, node, *child);
		} else {
			splitNode(*pval, mean, pval, pos, node, *child, child);

			return 1;
		}
	}

	return 0;
}

/* insert val in B-Tree */
void insertion(char word[], char mean[]) {
	int flag;
	char *i;
	struct node *child;

	flag = setValueInNode(word, mean, &i, root, &child);
	if (flag) {
		root = createNode(i, mean, child);
		}
}

/* copy successor for the value to be deleted */
void copySuccessor(struct node *myNode, int pos) {
	struct node *dummy;

	dummy = myNode->link[pos];

	for (;dummy->link[0] != NULL;)
		dummy = dummy->link[0];

	strcpy(myNode->word[pos], dummy->word[1]);

}

/* removes the value from the given node and rearrange values */
void removeVal(struct node *myNode, int pos) {
	int i = pos + 1;

	while (i <= myNode->count) {
		strcpy(myNode->word[i - 1], myNode->word[i]);
		myNode->link[i - 1] = myNode->link[i];
		i++;
	}
	myNode->count--;
}

/* shifts value from parent to right child */
void doRightShift(struct node *myNode, int pos) {
	struct node *x = myNode->link[pos];
	int j = x->count;

	while (j > 0) {
		strcpy(x->word[j + 1], x->word[j]);
		x->link[j + 1] = x->link[j];
	}
	strcpy(x->word[1], myNode->word[pos]);
	x->link[1] = x->link[0];
	x->count++;

	x = myNode->link[pos - 1];
	strcpy(myNode->word[pos], x->word[x->count]);
	myNode->link[pos] = x->link[x->count];
	x->count--;

	return;
}

/* shifts value from parent to left child */
void doLeftShift(struct node *myNode, int pos) {
	int j = 1;
	struct node *x = myNode->link[pos - 1];

	x->count++;
	strcpy(x->word[x->count], myNode->word[pos]);
	x->link[x->count] = myNode->link[pos]->link[0];

	x = myNode->link[pos];
	strcpy(myNode->word[pos], x->word[1]);
	x->link[0] = x->link[1];
	x->count--;

	while (j <= x->count) {
		strcpy(x->word[j], x->word[j + 1]);
		x->link[j] = x->link[j + 1];
		j++;
	}

	return;
}

/* merge nodes */
void mergeNodes(struct node *myNode, int pos) {
	int j = 1;
	struct node *x1 = myNode->link[pos], *x2 = myNode->link[pos - 1];

	x2->count++;
	strcpy(x2->word[x2->count], myNode->word[pos]);
	x2->link[x2->count] = myNode->link[0];

	while (j <= x1->count) {
		x2->count++;
		strcpy(x2->word[x2->count], x1->word[j]);
		x2->link[x2->count] = x1->link[j];
		j++;
	}

	j = pos;
	while (j < myNode->count) {
		strcpy(myNode->word[j], myNode->word[j + 1]);
		myNode->link[j] = myNode->link[j + 1];
		j++;
	}
	myNode->count--;
	free(x1);
}

int Node(struct node *myNode, int pos) {
	if (!pos) {
		if (myNode->link[1]->count > MIN) {
			doLeftShift(myNode, 1);
		} else {
			mergeNodes(myNode, 1);
		}
	} else {
		if (myNode->count != pos) {
			if(myNode->link[pos - 1]->count > MIN) {
				doRightShift(myNode, pos);
			} else {
				if (myNode->link[pos + 1]->count > MIN) {
					doLeftShift(myNode, pos + 1);
				} else {
					mergeNodes(myNode, pos);
				}
			}
		} else {
			if (myNode->link[pos - 1]->count > MIN)
				doRightShift(myNode, pos);
			else
				mergeNodes(myNode, pos);
		}
	}
}
/*adjusts the given node */
void adjustNode(struct node *myNode, int pos) {
	if (!pos) {
		if (myNode->link[1]->count > MIN) {
			doLeftShift(myNode, 1);
		} else {
			mergeNodes(myNode, 1);
		}
	} else {
		if (myNode->count != pos) {
			if(myNode->link[pos - 1]->count > MIN) {
				doRightShift(myNode, pos);
			} else {
				if (myNode->link[pos + 1]->count > MIN) {
					doLeftShift(myNode, pos + 1);
				} else {
					mergeNodes(myNode, pos);
				}
			}
		} else {
			if (myNode->link[pos - 1]->count > MIN)
				doRightShift(myNode, pos);
			else
				mergeNodes(myNode, pos);
		}
	}
}
/* delete val from the node */
int delValFromNode(char word[], struct node *myNode) {
	int pos, flag = 0;
	if (myNode) {
		if (strcmp(word, myNode->word[1]) < 0) {
			pos = 0;
			flag = 0;
		} else {
			for (pos = myNode->count; (strcmp(word, myNode->word[pos]) < 0 && pos > 1); pos--);
			if (strcmp(word, myNode->word[pos]) == 0) {
				flag = 1;
			} else {
				flag = 0;
			}
		}
		if (flag) {
			if (myNode->link[pos - 1]) {
				copySuccessor(myNode, pos);
				flag = delValFromNode(myNode->word[pos], myNode->link[pos]);
				if (flag == 0) {
					printf("Given word is not present in B-Tree\n");
				}
			} else {
				removeVal(myNode, pos);
			}
		} else {
			flag = delValFromNode(word, myNode->link[pos]);
		}
		if (myNode->link[pos]) {
			if (myNode->link[pos]->count < MIN)
				adjustNode(myNode, pos);
		}
	}

	return flag;
}

/* delete val from B-tree */
void deletion(char word[], struct node *myNode) {
	struct node *tmp;

	if (!delValFromNode(word, myNode)) {
		printf("Given word is not present in B-Tree\n");

		return;
	} else {
		if (myNode->count == 0) {
			tmp = myNode;
			myNode = myNode->link[0];
			free(tmp);
		}
	}
	root = myNode;

	return;
}

/* search val in B-Tree */
void searching(char word[], int *pos, struct node *myNode) {
	if (!myNode) {

		return;
	}

	if (strcmp(word, myNode->word[1]) < 0) {
		*pos = 0;
	} else {
		for (*pos = myNode->count; (strcmp(word, myNode->word[*pos]) < 0 && *pos > 1); (*pos)--);
		if (strcmp(word, myNode->word[*pos]) == 0) {
			printf("\nThe meaning of word %s is:", myNode->word[*pos]);
			FILE *fp;
			struct meaning m;

			fp = fopen("meanings.txt","r");
			fseek(fp,sizeof(struct meaning)*myNode->offset[*pos],SEEK_SET);
			fread(&m,sizeof(struct meaning),1,fp);
			printf("%s\n",m.mean);
			//printf("Offset = %d",myNode->offset[*pos]);
			fclose(fp);

			return;
		}
	}
	searching(word, pos, myNode->link[*pos]);

	return;
}

/* B-Tree Traversal */
void traversal(struct node *myNode) {
	int i;
	if (myNode) {
		for (i = 0; i < myNode->count; i++) {
			traversal(myNode->link[i]);
			printf("%s ", myNode->word[i + 1]);
			//printf("%d", myNode->offset[i+1]);
		}
		traversal(myNode->link[i]);
	}
}

int main()
{
	int ch;
	char word[26];
	char mean[26];

	while (1) {
		printf("1. Insertion\t2. Deletion\n");
		printf("3. Searching\t4. Traversal\n");
		printf("5. Exit\nEnter your choice:");
		scanf("%d", &ch);

		switch (ch) {
			case 1:
				printf("Enter the word:");
				scanf("%s", word);
				printf("Enter the meaning:");
				scanf("%s", mean);
				insertion(word,mean);
				break;
			case 2:
				printf("Enter the element to delete:");
				scanf("%s", word);
				deletion(word, root);
				break;
			case 3:
				printf("Enter the element to search: ");
				scanf("%s", word);
				searching(word, &ch, root);
				break;
			case 4:
				traversal(root);
				break;
			case 5:
				exit(0);
			default:
				printf("You have entered wrong option!!\n");
				break;
		}
		printf("\n");
	}

	return 0;
}
