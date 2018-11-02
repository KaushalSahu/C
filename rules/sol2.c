#include <stdio.h>
#include <math.h>

double A;
int x[3];
int y[3];

float distance(int x1, int y1, int x2, int y2);
float area(int X1, int Y1, int X2, int Y2, int X3, int Y3);
int tritest(int d, int s);

void main()
{
	int n;
	int r;
	int o;
	int w;

	printf("Enter x and y coordinates of 1st point\n");
	scanf("%d%d", &x[0], &y[0]);
	printf("Enter x and y coordinates of 2nd point\n");
	scanf("%d%d", &x[1], &y[1]);
	printf("Enter x and y coordinates of 3rd point\n");
	scanf("%d%d", &x[2], &y[2]);

	A = area(x[0], y[0], x[1], y[1], x[2], y[2]);

	printf("Enter total number of points to be checked\n");
	scanf("%d", &n);

	int X[n];
	int Y[n];

	for (o = 0; o < n; o++) {
		printf("Enter x and y co-ordinates of point to be checked\n");
		scanf("%d%d", &X[o], &Y[o]);
	}

	for (w = 0; w < n; w++) {
		r = tritest(X[w], Y[w]);

		if (r == 1) {
			printf("Point (%d,%d) lies inside triangle\n", X[w], Y[w]);
		} else {
			printf("point (%d,%d) lies outside the triangle\n", X[w], Y[w]);
		}
	}
}

int tritest(int d, int s)
{
	double A1;
	double A2;
	double A3;

	A1 = area(x[0], y[0], x[1], y[1], d, s);
	A2 = area(x[0], y[0], d, s, x[2], y[2]);
	A3 = area(d, s, x[1], y[1], x[2], y[2]);

	if (A == A1 + A2 + A3) {
		return 1;
	} else {
		return 0;
	}
}

float distance(int x1, int y1, int x2, int y2)
{
	float dis;

	dis = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));

	return dis;
}

float area(int X1, int Y1, int X2, int Y2, int X3, int Y3)
{
	float l1;
	float l2;
	float l3;
	float s;
	float a;

	l1 = distance(X1, Y1, X2, Y2);
	l2 = distance(X2, Y2, X3, Y3);
	l3 = distance(X3, Y3, X1, Y1);
	s = (l1 + l2 + l3) / 2.0;
	a = sqrt(s * (s - l1) * (s - l2) * (s - l3));

	return a;
}
