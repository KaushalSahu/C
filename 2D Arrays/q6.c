#include <stdio.h>

int main()
{
	int i;
	int j;
	int n;

	scanf("%d", &n);

	int col[n];
	int row[n];
	int a[n][n];

	for(i = 0; i < n; i++) {
		row[i] = 0;

		for(j = 0; j < n; j++) {
			if(i == 0) {
				col[j] = 0;
			}

			scanf("%d", &a[i][j]);
			row[i] = row[i] + a[i][j];
			col[j] = col[j] + a[i][j];
		}
	}

	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			if(row[i] == col[j]) {
				printf("\nRow: %d \nColumn: %d", i+1, j+1);

				return 0;
			}
		}

	}

	return 0;
}
