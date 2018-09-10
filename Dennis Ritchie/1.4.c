#include<stdio.h>
main()
{
float farh,cel;
int low,up,step;
low=0,up=300,step=20;
cel=low;
printf("Fahrenheit\tCelsius\n");
while(cel<=up)
{
farh=(cel+32.0)*9.0/5.0;
printf("  %3.0f\t\t%6.1f\n",cel,farh);
cel=cel+step;

}
}
