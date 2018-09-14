#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long  cal_hash(char c[20], long mod) {
	
	int i = 0;
	unsigned long hash = 5381;

	while (c[i] != '\0') {
		hash = (hash * 33) + c[i];
		i++;
	}

	hash = (hash % mod);
	
	return hash;
}

int main()
{
	char ch[20][10];
	char c[20][20];
	
	int arr[1097] = {0};
	long mod = 1097;
	unsigned long hash;
	
	int n;
	int i = 0;
	int cnt = 0;
	
	scanf("%d", &n);

	while (i < n) {
		scanf("%s", ch[i++]);
	}	
	
	i = 0;
	while (i < n-1) {
		strcpy(c[i], ch[i]);
		strcat(c[i], ch[i+1]);
		i++;	
	}
	
	i = 0;
	while (i < n-1) {
		
		hash = cal_hash(c[i], mod);
		
		if (arr[hash] == 0) {
			arr[hash]++;
			cnt++;
		}
		else 
			arr[hash]++;

		i++;
	}
		
	printf("%d\n", cnt);
	
	return 0;
}
