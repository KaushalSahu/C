#include <stdio.h>

int main()
{
	int n;
	int i;
	int j;
	int sum;
	int max;
	int pos;

	pos = 0;

	scanf("%d",&n);
	int a[n][n];

	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			scanf("%d",&a[i][j]);
		}
	}

	max = a[0][0];

	for(i=0;i<n;i++) {
		sum = 0;
		j = i;

		if(i!=n-1 && i==0 && j==0) {
			sum = a[i][j+1]+a[i+1][j]+a[i+1][j+1];
		}
		else if(i==n-1 && j==n-1) {
			sum = a[i-1][j-1]+a[i-1][j]+a[i][j-1];
		}
		else {
			sum = a[i-1][j-1]+a[i-1][j]+a[i-1][j+1]+a[i][j-1]+a[i][j+1]+a[i+1][j-1]+a[i+1][j]+a[i+1][j+1];
		}

		printf("%d:%d\n",a[i][i],sum);

		if(sum>max) {
			max = sum;
			pos = i;
		}

	}

	if(n==1) {
		printf("%d",a[0][0]);
	}
	printf("index:%d\n",pos+1);

	return 0;
}
