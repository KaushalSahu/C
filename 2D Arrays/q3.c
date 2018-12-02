#include <stdio.h>

void transpose(int *m, int *n, int a[][*n])
{
	int i;
	int j;
	int arr[*n][*m];

	for(i = 0;i < *m; i++) {
		for(j = 0; j < *n; j++) {
			arr[j][i] = a[i][j];
		}
	}
	for(i = 0; i < *n; i++) {
		for(j = 0; j < *m; j++) {
			printf("%d ", arr[i][j]);
		}

		printf("\n");
	}
}

int main()
{
	int m;
	int n;
	int i;
	int j;

	scanf("%d", &m);
	scanf("%d", &n);
	int a[m][n];

	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	transpose(&m, &n, a);

	return 0;
}
