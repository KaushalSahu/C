#include<stdio.h>
#include<string.h>
int max(int a,int b)
{
	if(a>b)
	return a;

	return b;
}
int main()
{
	int n;
	int i;
	int k;
	int j;
	
	scanf("%d",&n);
	getchar();
	
	char a[5][26];
	
	for(i=0;i<n;i++){
		scanf("%s",&a[i][0]);
		getchar();
	}
	
	int count[26];
	
	for(i=0;i<26;i++){
		count[i]=0;
	}
	
	for(j=0;j<25;j++){
		int s[256]={0};
		for(i=0;i<n;i++){
			if(j<strlen(a[i])){
			s[a[i][j]]++;
			}
		}

		int c=0;

		for(k=0;k<256;k++){
			c=max(c,s[k]);
		}
		count[j]=c;
	}

	int index=-1;
	int occur=0;

	for(i=0;i<25;i++){
		if(count[i]>occur){
			index=i;
			occur=count[i];
		}
	}
	
	printf("%d : ",index+1);
	
	float p=occur;
	char c='%';	

	printf("%4.1f%c\n",(p*100)/n,c);
}
