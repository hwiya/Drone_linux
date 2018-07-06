#include <signal.h>
#include<stdio.h>
#include<unistd.h>

//SIGINT에 대응하는 핸들러
void sigHandler(int sig)
{
	printf("OUCH! - i got signal %d\n",sig);
}

int main()
{
	signal(SIGINT, sigHandler);

	while(1)
	{
		printf("Hello World!\n");
		sleep(1);
	}
}
