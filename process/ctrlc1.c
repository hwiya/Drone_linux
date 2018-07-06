#include <signal.h>
#include<stdio.h>
#include<unistd.h>

//SIGINT에 대응하는 핸들러
void sigHandler(int sig)
{
	switch(sig)
	{
	case SIGINT:
		printf("SIGINT %d\n",sig);
		(void) signal(SIGINT, SIG_DFL);
		break;
	case SIGQUIT:
		printf("SIGQUIT %d\n",sig);
		(void) signal(SIGQUIT, SIG_DFL);
		break;
	}
}

int main()
{
	signal(SIGINT, sigHandler);
	signal(SIGQUIT, sigHandler);

	while(1)
	{
		printf("Hello World!\n");
		sleep(1);
	}
}
