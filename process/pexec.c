#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	printf("Runnig ps with execlp\n");
	system("ps -ax");
	printf("Done\n");
	return 5;
}
