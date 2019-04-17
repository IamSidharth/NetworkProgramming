#include<stdio.h>
#include<string.h>

int main()

{
	char buff[50];
	strcpy(buff,"hello");
	
	int arr[5];

	int temp[5]={1,2,3,4};

	memcpy(arr,temp,sizeof(arr));

	//puts(arr);
	int i=0;
	for(i=0;i<3;i++)
		printf("\n%d\n",arr[i]);
}