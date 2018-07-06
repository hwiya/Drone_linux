#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void sigHandle(int sig)
{
	static int count = 1;
	if(count == 5)
	{
		exit(0);
	}
	else if(count < 5)
	{	
		printf("killTest : I got signal %d\n", sig);
		count++;
	}
}

int main(void)
{
	signal(SIGINT, sigHandle);
	while(1)
	{
		printf("Hello World\n");
		sleep(1);
	}
}
