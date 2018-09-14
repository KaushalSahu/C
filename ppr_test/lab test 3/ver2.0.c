#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	char *data;
	struct node* next;
};

int equal(char *a,char *b)
{
	int l=strlen(a);
	int l2=strlen(b);
	if(l<l2)l=l2;
	int flag=0;
	for(int i=0;i<l;i++)
	{
		if(a[i]!=b[i])
		{
			flag=1;
		}
	}
	if(flag==0)return 1;
	else return 0;
}


int main(void)
{
	int n;
	int i,j,sum,count,hash,flag,k;
	char input[20][10];
	scanf("%d",&n);
	struct node* arr[20];
	
	for(i=0;i<n;i++)
	{
		scanf("%s",input[i]);
	}
	for(i=0;i<20;i++)
	{
		arr[i]=NULL;
	}
	for(i=0;i<(n-1);i++)
	{
		j=0;
		sum=0;
		while(input[i][j]!='\0')
			{
				sum+=input[i][j];
				j++;
			}
		hash=sum % 20;
		if(arr[hash] == NULL)
		{
			struct node *temp;
			temp=(struct node*)malloc(sizeof(struct node));
			temp->data=(char*)malloc(10*sizeof(char));
			temp->data=input[i+1];
			temp->next=NULL;
			arr[hash]=temp;
		}
		else
		{
			struct node* ptr=arr[hash];
			flag=0;
			while(1)			//collison resolution by chaining
			{
				//printf("%s %s\n",ptr->data,input[i+1]);
				if(equal(ptr->data,input[i+1]))
				{
					//printf("second");
					flag=1;
					break;
				}
				ptr=ptr->next;
				if(ptr==NULL)break;
				
			}
			if(flag==0)
			{
				//printf("inside");
				struct node *temp;
				temp=(struct node*)malloc(sizeof(struct node));
				temp->data=(char*)malloc(10*sizeof(char));
				temp->data=input[i+1];
				temp->next=arr[hash];
				arr[hash]=temp;
				//printf("%s %s",arr[hash]->data,temp->next->data);
			}
		}

	}
	count=0;
	for(i=0;i<20;i++)
	{
		if(arr[i]!=NULL)
		{
			struct node *ptr=arr[i];
			while(ptr!=NULL)
			{
				count++;
				ptr=ptr->next;
			}
		}
	}
	printf("%d",count);
	return 0;
}
