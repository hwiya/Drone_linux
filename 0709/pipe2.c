#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	int data_processed;
	int file_pipes[2];
	const char some_data[] = "123";
	const char some_data2[] = "456";
	char buffer[BUFSIZ + 1];
	pid_t fork_result;
	int status;

	memset(buffer, '\0', sizeof(buffer));

	if(pipe(file_pipes) == 0)
	{
		fork_result = fork();
		if(fork_result == -1)
		{
			fprintf(stderr, "Fork failure");
			exit(EXIT_FAILURE);
		}
		if(fork_result == 0)
		{
			data_processed = read(file_pipes[0], buffer, BUFSIZ);
			buffer[data_processed] = '\0';
			printf("Child Read %d bytes : %s\n", data_processed, buffer);
			
			close(file_pipes[0]);
			close(file_pipes[1]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			data_processed = write(file_pipes[1], some_data, strlen(some_data));
			printf("Parent Wrote %d bytes\n", data_processed);
			
			wait(&status);
		}
	}

	close(file_pipes[0]);
	close(file_pipes[1]);
	exit(EXIT_SUCCESS);
}
