#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node {
	int src;
	int dest;
	int weight;
};

int get_index(char *city, char *ar[], int *index) 
{
	int i;
	for(i = 0; i < (*index); i++) {
		if(strcmp(ar[i], city) == 0) {
			return i;
		}
	}
	ar[*index] = city;
	return (*index)++;
}

int comp(const void *p, const void *q) {
	return ((struct node *)p)->weight - ((struct node *)q)->weight;
}

int root(int a, int id[]) {
	while(id[a] != a) {
		id[a] = id[id[a]];
		a = id[a];
	}
	return a;
}

void union1(int a, int b, int id[]) {
	int p = root(a, id);
	int q = root(b, id);
	id[p] = id[q];	
}

void intialize(int id[], int size) {
	int i;
	for(i = 0; i < size; i++) {
		id[i] = i;
	}
}



int krushkal(struct node p[], int k) 
{
	int id[1000];
	intialize(id,1000);
	int i;
	int min_cost = 0;
	for(i = 0; i < k; i++) {
		int x = p[i].src;
		int y = p[i].dest;
		int cost = p[i].weight;
		if(root(x, id) != root(y, id)) {
			min_cost += cost;
			union1(x, y, id);
		}
	}
	return min_cost;
}


int main()
{
	int n;
	scanf("%d", &n);	
	struct node p[1000];
	char *src;
	char *dest;
	int index = 0;
	char *ar[1000];
	int k;
	for (k = 0; k < n; k++) {
		src = (char *)malloc(100 * sizeof(char));
		dest = (char *)malloc(100 * sizeof(char));
		scanf("%s", src);
		scanf("%s", dest);
		p[k].src = get_index(src, ar, &index);
		p[k].dest = get_index(dest, ar, &index);
		scanf("%d", &p[k].weight);
	}	
	qsort(p, n, sizeof(struct node), comp);	
	printf("mincost : %d\n", krushkal(p, k));
	return 0;
}
