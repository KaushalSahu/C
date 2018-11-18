#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX 4 //maximum number of values in a node
#define MIN 2 //minimum number of values in a node

struct stat file;
//MAX = (file.st_blksize+34)/42;

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

void writeToFile(char mean[])
{
	struct meaning m;
	FILE *fp;
	fp = fopen("meanings.bin", "a+");

	if (fp == NULL) {
		printf("meanings file not found\n");
		return;
	}

	strcpy(m.mean, mean);
	fwrite(&m, sizeof(struct meaning), 1, fp);
	fclose(fp);
}

struct node * createNode(char word[], char mean[], struct node *child, int num) {
	struct node *newNode;

	newNode = (struct node *) malloc(sizeof(struct node));

	strcpy(newNode->word[1],word);
	newNode->count = 1;
	newNode->link[0] = root;
	newNode->link[1] = child;
	newNode->offset[1] = num;

	return newNode;
}

/* Places the word in appropriate position */
void addWordToNode(char word[],char mean[], int num,  int pos, struct node *node, struct node *child) {
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
	node->offset[j+1] = num;
}

/* split the node */
void splitNode (char word[], char mean[], int *off, char **pword, int pos, struct node *node, struct node *child, struct node **newNode) {
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
		(*newNode)->offset[j - median] = node->offset[j];
		j++;
	}

	node->count = median;
	(*newNode)->count = MAX - median;

	if (pos <= MIN) {
		addWordToNode(word,mean,*off, pos, node, child);
	} else {
		addWordToNode(word,mean,*off, pos - median, *newNode, child);
	}

	strcpy(*pword, node->word[node->count]);
	*off = node->offset[node->count];
	(*newNode)->link[0] = node->link[node->count];
	(*newNode)->offset[0] = node->offset[node->count];
	node->count--;
}

/* sets the word in the node */
int setWordInNode(char word[], char mean[],int num, int *off, char **pword, struct node *node, struct node **child) {
	int pos;

	if (node == NULL) {
		*pword = word;
		*off = num;
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
	if (setWordInNode(word, mean, num,off, pword, node->link[pos], child)) {
		if (node->count < MAX) {
			addWordToNode(*pword,mean,*off, pos, node, *child);

		} else {
			splitNode(*pword, mean, off, pword, pos, node, *child, child);

			return 1;
		}
	}

	return 0;
}

/* insert word in B-Tree */
void insertion(char word[], char mean[], int num) {
	int flag;
	char *i;
	int off;
	struct node *child;

	flag = setWordInNode(word, mean,num, &off, &i, root, &child);
	if (flag) {
		root = createNode(i, mean, child, off);
	}
}

/*To modify meaning of word in dictionary*/
void modify(char word[],char mean[], int *pos, struct node *myNode) {
	if (!myNode) {

		return;
	}

	if (strcmp(word, myNode->word[1]) < 0) {
		*pos = 0;
	} else {
		for (*pos = myNode->count; (strcmp(word, myNode->word[*pos]) < 0 && *pos > 1); (*pos)--);
		if (strcmp(word, myNode->word[*pos]) == 0) {
			FILE *fp;
			struct meaning m;

			strcpy(m.mean, mean);
			fp = fopen("meanings.bin","r+");
			if (fp == NULL) {
				printf("meanings file not found\n");
				return;
			}
			fseek(fp,sizeof(struct meaning)*myNode->offset[*pos],SEEK_SET);
			fwrite(&m, sizeof(struct meaning), 1, fp);
			fclose(fp);

			return;
		}
	}
	modify(word,mean, pos, myNode->link[*pos]);

	return;
}

/* copy successor for the word to be deleted */
void copySuccessor(struct node *myNode, int pos) {
	struct node *dummy;

	dummy = myNode->link[pos];

	for (;dummy->link[0] != NULL;)
		dummy = dummy->link[0];

	strcpy(myNode->word[pos], dummy->word[1]);

}

/* removes the word from the given node and rearrange words */
void removeWord(struct node *myNode, int pos) {
	int i = pos + 1;

	while (i <= myNode->count) {
		strcpy(myNode->word[i - 1], myNode->word[i]);
		myNode->offset[i-1] = myNode->offset[i];
		myNode->link[i - 1] = myNode->link[i];
		i++;
	}

	myNode->count--;
}

/* shifts word from parent to right child */
void doRightShift(struct node *myNode, int pos) {
	struct node *x = myNode->link[pos];
	int j = x->count;

	while (j > 0) {
		strcpy(x->word[j + 1], x->word[j]);
		x->offset[j+1] = x->offset[j];
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

/* shifts word from parent to left child */
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
		x->offset[j] = x->offset[j+1];
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
	x2->link[x2->count] = x1->link[0];

	while (j <= x1->count) {
		x2->count++;
		strcpy(x2->word[x2->count], x1->word[j]);
		x2->link[x2->count] = x1->link[j];
		x2->offset[x2->count] = x1->offset[j];
		j++;
	}

	j = pos;
	while (j < myNode->count) {
		strcpy(myNode->word[j], myNode->word[j + 1]);
		myNode->link[j] = myNode->link[j + 1];
		myNode->offset[j] = myNode->offset[j + 1];
		j++;
	}
	myNode->count--;
	free(x1);
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

/* delete word from the node */
int delWordFromNode(char word[], struct node *myNode) {
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
				flag = delWordFromNode(myNode->word[pos], myNode->link[pos]);
				if (flag == 0) {
					printf("Given word is not present in B-Tree\n");
				}
			} else {
				removeWord(myNode, pos);
			}
		} else {
			flag = delWordFromNode(word, myNode->link[pos]);
		}
		if (myNode->link[pos]) {
			if (myNode->link[pos]->count < MIN)
				adjustNode(myNode, pos);
		}
	}

	return flag;
}

/* delete word from B-tree */
void deletion(char word[], struct node *myNode) {
	struct node *tmp;

	if (!delWordFromNode(word, myNode)) {
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

/* search word in B-Tree */
void search(char word[], int *pos, struct node *myNode) {
	if (!myNode) {

		return;
	}

	if (strcmp(word, myNode->word[1]) < 0) {
		*pos = 0;
	} else {
		for (*pos = myNode->count; (strcmp(word, myNode->word[*pos]) < 0 && *pos > 1); (*pos)--);
		if (strcmp(word, myNode->word[*pos]) == 0) {
			printf("\nThe meaning of word %s is:", myNode->word[*pos]);
			//printf("Offset = %d",myNode->offset[*pos]);
			FILE *fp;
			struct meaning m;

			fp = fopen("meanings.bin","r");
			fseek(fp,sizeof(struct meaning)*myNode->offset[*pos],SEEK_SET);
			fread(&m,sizeof(struct meaning),1,fp);
			printf("%s\n",m.mean);
			fclose(fp);

			return;
		}
	}
	search(word, pos, myNode->link[*pos]);

	return;
}

/* B-Tree Traversal */
void Print(struct node *myNode) {
	int i;
	if (myNode) {
		for (i = 0; i < myNode->count; i++) {
			Print(myNode->link[i]);
			printf("%s:", myNode->word[i + 1]);
			FILE *fp;
			struct meaning m;

			fp = fopen("meanings.bin","r");
			fseek(fp,sizeof(struct meaning)*myNode->offset[i+1],SEEK_SET);
			fread(&m,sizeof(struct meaning),1,fp);
			printf("%s, ",m.mean);
			fclose(fp);
		}
		Print(myNode->link[i]);
	}
}

int main()
{
	int ch;
	int num = 0;
	char word[26];
	char mean[26];

	while (1) {
		printf("1. Insert\t2. Modify\t3.Delete\n");
		printf("4. Search\t5. Print\t6. Exit\nEnter your choice:");
		scanf("%d", &ch);

		switch (ch) {
			case 1:
				printf("Enter the word:");
				scanf(" %[^\n]s", word);
				printf("Enter the meaning:");
				scanf(" %[^\n]s", mean);
				writeToFile(mean);
				insertion(word, mean, num++);
				break;
			case 2:
				printf("Enter the word for replacing the meaning : ");
				scanf(" %[^\n]s", word);
				printf("Enter the meaning : ");
				scanf(" %[^\n]s", mean);
				modify(word, mean, &ch, root);
				break;
			case 3:
				printf("Enter the element to delete:");
				scanf(" %[^\n]s", word);
				deletion(word, root);
				break;
			case 4:
				printf("Enter the element to search: ");
				scanf(" %[^\n]s", word);
				search(word, &ch, root);
				break;
			case 5:
				Print(root);
				printf("\n");
				break;
			case 6:
				system("rm meanings.bin");
				exit(0);
			default:
				printf("You have entered wrong option!!\n");
				break;
		}
		printf("\n");
	}

	return 0;
}
