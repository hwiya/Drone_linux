#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#define BUFSIZE 1024

//int main(int argc, char **argv) 아래와 동일한 표현
int main(int argc, char *argv[])
{
	int count, fdIN, fdOUT;
	char buf[BUFSIZE];

	if(argc <3)//인자값이 3개가 아닌 경우
	{
		//printf("Usage : copy file1 file2\n");
		//fflush(stdout);
		write(1,"Usage : copy file1 file2\n",26);
		return -1;
	}
	//원본 파일이 정상적으로 열리지 않는 경우
	if((fdIN = open(argv[1], O_RDONLY)) < 0)
	{
		perror(argv[1]);
		return -1;
	}
	//대상 파일이 정상적으로 열리지 않는 경우
	if((fdOUT = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR \
				| S_IWUSR)) < 0)
	{
		perror(argv[2]);
		return -1;
	}
	while((count = read(fdIN, buf, sizeof(buf))) > 0)
	{
		write(fdOUT, buf, count);
	}
	close(fdIN);
	close(fdOUT);

	return 0;
}
