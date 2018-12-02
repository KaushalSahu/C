#include <stdio.h>
#include <string.h>

#define n1 puts("")

void sort(char (*names)[], int n)
{
	int i;
	int j;
	char (*temp)[30] = names;
	char key[30];

	for(i = 0; i < n; i++) {
		strcpy(key, temp[i]);
		j = i-1;

		while(j >= 0 && strcmp(key, temp[j]) < 0) {
			strcpy(temp[j+1], temp[j]);
			j--;
		}
		strcpy(temp[j+1], key);
	}
}

int main()
{
	int n;
	int i;

	scanf("%d", &n);

	char names[n][30];
	char prev[30];

	for(i = 0; i < n; i++) {
		scanf("%s", names[i]);
	}

	sort(names, n);

	puts("Sorted :");

	for(i = 0; i < n; i++) {
		printf("%s ", names[i]);
	}
	n1;

	puts("Unique:");

	for(i = 0; i < n; i++) {
		if(i == 0) {

			printf("%s ", names[i]);
		} else if(strcmp(prev, names[i]) != 0) {

			printf("%s ", names[i]);
		}

		strcpy(prev, names[i]);
	}

	n1;

	return 0;
}
