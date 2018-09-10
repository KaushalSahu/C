//EOF from user input can be given by using ctrl+D
#include<stdio.h>
int main() {
	int c;
    while ((c = getchar()) != EOF) {
        printf("\t%d\t ", c != EOF);
        putchar(c);
    }
    printf("\n%d\n", c != EOF);
	return 0;
}

