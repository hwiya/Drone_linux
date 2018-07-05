#include<stdio.h>
#include<stdlib.h>

#define mem_size 200

int a = 10;
int b = 0;
int array[10];
int const img[5] = {0, 1, 2, 3, 4};
char *pData = "Hello World";

int main()
{
	static int c;
	static int d = 15;
	char label[100];
	char *pLabel;

	pLabel = malloc(sizeof(char)*mem_size);
	scanf("%s",pLabel);
	printf("%s\n",pLabel);
	
	printf("%s\n",pData);
	pData = "hi";
	printf("%s\n",pData);
	free(pLabel);
}
