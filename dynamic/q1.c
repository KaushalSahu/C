#include <stdio.h>
#include <stdlib.h>

void print(int capacity, int n, int* temp)
{
	int i;

	printf("capacity = %2d; size = %2d; elements = ", capacity, n);

	for(i = 0; i < n; i++) {
		printf(" %d", temp[i]);
	}
	printf("\n");
}

int* push_back(int a[], int n)
{
	int *temp, *temp2, capacity;
	int i, j;
	capacity = 0;

	for(i = 0; i < n; i++) {
		if(capacity == i) {
			if(capacity == 0) {
				capacity = 1;
				temp = (int*) malloc(sizeof(int)*capacity);
				temp[i] = a[i];
			} else {
				capacity = capacity * 2;
				temp2 = (int*) malloc(sizeof(int)*capacity);
				for(j = 0; j <= i; j++) {
					temp2[j] = a[j];
				}
				free(temp);
				temp = temp2;
			}
		} else {
			temp[i] = a[i];
		}
		print(capacity, i+1, temp);
	}
	return temp;
}

int main()
{
	int n;
	int i;

	scanf("%d", &n);

	int a[n];

	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	push_back(a, n);
}
