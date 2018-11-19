#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX 30 
#define MIN 15 

struct stat file;
//MAX = (file.st_blksize+34)/42;

struct node {
	int count;
	int offset[MAX+1];
	char word[MAX+1][26];
	struct node *link[MAX+1];
};

struct meaning {
	char word[50];
	char mean[150];
};

struct node *root = NULL;

void writeToFile(char word[], char mean[])
{
	struct meaning m;
	FILE *fp;
	fp = fopen("dictionary.bin", "a+");

	if (fp == NULL) {
		printf("meanings file not found\n");
		return;
	}
	strcpy(m.word, word);
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

			strcpy(m.word, word);
			strcpy(m.mean, mean);
			fp = fopen("dictionary.bin","r+");
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

			fp = fopen("dictionary.bin","r");
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

			fp = fopen("dictionary.bin","r");
			fseek(fp,sizeof(struct meaning)*myNode->offset[i+1],SEEK_SET);
			fread(&m,sizeof(struct meaning),1,fp);
			printf("%s\n",m.mean);
			fclose(fp);
		}
		Print(myNode->link[i]);
	}
}

int Load(int num) {

	FILE *fp;
	struct meaning m;

	fp = fopen("dictionary.bin","r");
	if (fp == NULL) {
		printf("meanings file not found\n");
		return 0;
	}
	while(fread(&m,sizeof(struct meaning),1,fp))
	{
		insertion(m.word,m.mean,num++);
		//printf("%s:%s:%d,",m.word,m.mean,num);
	}
	fclose(fp);
	return num;
}

int main()
{
	int ch;
	int num = 0;
	char word[50];
	char mean[150];

	/*for(int i = 0;i<100;i++)
	  {
	  scanf(" %[^\n]s", word);
	  scanf(" %[^\n]s", mean);
	  writeToFile(word,mean);
	  insertion(word, mean, num++);

	  }*/
	num = Load(num);
	while (1) {
		printf("\n1. Insert\t2. Modify\t\n");
		printf("3. Search\t4. Print\t5. Exit\nEnter your choice:");
		scanf("%d", &ch);

		switch (ch) {
			case 1:
				printf("Enter the word:");
				scanf(" %[^\n]s", word);
				printf("Enter the meaning:");
				scanf(" %[^\n]s", mean);
				writeToFile(word,mean);
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
				printf("Enter the element to search: ");
				scanf(" %[^\n]s", word);
				search(word, &ch, root);
				break;
			case 4:
				Print(root);
				printf("\n");
				break;
			case 5:
				exit(0);
			default:
				printf("You have entered wrong option!!\n");
				break;
		}

	}
	printf("\n");
	return 0;
}
