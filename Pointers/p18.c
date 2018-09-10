#include <stdio.h>
#include <string.h>

int main()
{
	char s1[] = "Hello world";
	char s2[100];

	printf("s1 is of length %d\n", strlen(s1));
	printf("s2 is of length %d\n", strlen(s2));

	/*
	 * char *strcpy(char *dest, const char *src);
	 */
	strcpy(s2, s1);

	printf("%s\n", s1);
	printf("%s\n", s2);
	printf("s2 is of length %d\n", strlen(s2));


	return 0;
}
