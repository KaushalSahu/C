#include<stdio.h>
int main()
{
int c,b=0,t=0,l=0;
while((c=getchar())!=EOF)
{
if(c==' ')
b++;
if(c=='\t')
t++;
if(c=='\n')
l++;
}
printf("Blanks=%d\nTabs=%d\nNew lines=%d\n",b,t,l);
return 0;
}
