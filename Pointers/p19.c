#include <stdio.h>
#include <string.h>

int main()
{
	char s2[] = "World";
	char s1[] = "Hello";
	int i;

	/*
	 * int strcmp(const char *s1, const char *s2);
	 */

	i = strcmp(s1, s2);
	printf("%s cmp %s = %d\n", s1, s2, i);

	i = strcmp(s1, s1);
	printf("%s cmp %s = %d\n", s1, s1, i);

	i = strcmp(s2, s1);
	printf("%s cmp %s = %d\n", s2, s1, i);

	return 0;
}

