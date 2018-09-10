#include<stdio.h>
#define LOW 0
#define UP 300
#define STEP 20
main()
{
int farh;
for(int farh=LOW;farh<=UP;farh+=STEP)
printf("%3d %6.2f\n",farh,5.0/9.0*(farh-32.0));
}
