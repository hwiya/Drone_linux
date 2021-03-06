#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include"snddata.h"

int main()
{
	int running = 1;
	struct Person person[MAX_PERSON];
	int msgid, i;
	char buffer[BUFSIZ];

	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error : %d\n", errno);
		exit(EXIT_FAILURE);
	}
	
	// 1. Generate data
	for(i = 0;i < MAX_PERSON; i++)
	{
		person[i].my_msg_type = 1;
		sprintf(person[i].name, "lee%d", i);
		person[i].age = 20+i;
		person[i].id = i;
	}
	// 1.5 data printf

	// 2. send data
	for(i = 0; i < MAX_PERSON; i++)
	{
			
		if(msgsnd(msgid, (void *)&person[i], sizeof(person[i]), 0) == -1)
		{
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}
	}

	// msg queue 종료를 위한 메시지 생성
	person[0].my_msg_type = 3;
	if(msgsnd(msgid, (void *)&person[i], sizeof(person[0]), 0) == -1)
	{
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
	}
	if(person[0].my_msg_type == 3)
	{
		running = 0;
	}
	
	exit(EXIT_SUCCESS);
}
