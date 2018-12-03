#include<stdio.h>
#include<stdlib.h>
#define SIZE 20

struct node
{
	int data;
	int key;
};
struct node* hashArray[SIZE]; 

int hashCode(int key) {
	return key % SIZE;
}
void insert(int key,int data) {

	struct node *item = (struct node*) malloc(sizeof(struct node));
	item->data = data;  
	item->key = key;

	int hashIndex = hashCode(key);

	while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) 
	{
		++hashIndex;
		hashIndex %= SIZE;
	}

	hashArray[hashIndex] = item;
}

struct node *search(int key) {

	int hashIndex = hashCode(key);  

	while(hashArray[hashIndex] != NULL) 
	{

		if(hashArray[hashIndex]->key == key)
			return hashArray[hashIndex]; 

		++hashIndex;

		hashIndex %= SIZE;
	}        

	return NULL;        
}
struct node* delete(struct node *dummyItem, struct node* item) 
{
	int key = item->key;

	int hashIndex = hashCode(key);

	while(hashArray[hashIndex] != NULL) 
	{
		if(hashArray[hashIndex]->key == key) 
		{
			struct node* temp = hashArray[hashIndex]; 
			hashArray[hashIndex] = dummyItem; 
			return temp;
		}
		++hashIndex;
		hashIndex %= SIZE;
	}      

	return NULL;        
}
void display() {

	for(int i = 0; i<SIZE; i++) {

		if(hashArray[i] != NULL)
			printf(" (%d,%d)",hashArray[i]->key,hashArray[i]->data);
		else
			printf(" ~~ ");
	}
	printf("\n");
}

int main()
{
	int n;
	int num;
	int temp;
	struct node *item =(struct node*)malloc(sizeof(struct node));
	struct node *dummyItem =(struct node*)malloc(sizeof(struct node));
	dummyItem->data = -1;  
	dummyItem->key = -1; 

	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&num);
		insert(i,num);
	}

	display();

	scanf("%d",&temp);
	item = search(temp);

	if(item != NULL) 
	{
		printf("Element found: %d\n", item->data);
	} 
	else 
	{
		printf("Element not found\n");
	}
	scanf("%d",&temp);
	delete(dummyItem, item);
	item = search(temp);
	display();

	if(item != NULL) {
		printf("Element found: %d\n", item->data);
	} else {
		printf("Element not found\n");
	}

}
