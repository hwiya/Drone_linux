#include <signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

//SIGINT에 대응하는 핸들러
void sigHandler(int sig)
{
	static int count = 0;
	static int count1 = 0;
	switch(sig)
	{
	case SIGINT:
		printf("SIGINT %d\n",sig);
		
		count++;
		if(count == 5)
		{
			exit(0);
		}
		break;
	case SIGQUIT:
		printf("SIGQUIT %d\n",sig);
		
		count1++;
		if(count1 == 5)
		{
			exit(0);
		}
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
