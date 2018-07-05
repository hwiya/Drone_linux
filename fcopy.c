#include <stdio.h>

int main(int argc, char **argv)
{
	int count;
	FILE *in, *out;
	char buf[BUFSIZ];

	if(argc < 3)
	{
		fprintf(stderr, "Usage : fcopy file1 file2\n");	
		return -1;
	}
	if((in = fopen(argv[1], "r"))==NULL) //원본파일 열기
	{
		perror(argv[1]);
		return -1;
	}
	if((out = fopen(argv[2], "w"))==NULL)//대상파일 열기
	{
		perror(argv[2]);
		return -1;
	}
	//원본파일의 내용을 읽어서 대상파일에 쓰기
	while((count = fread(buf, sizeof(char), BUFSIZ, in)) > 0)
	{
		fwrite(buf, sizeof(char), count, out);
	}

	fclose(out);
	fclose(in);

	return 0;
	//printf("BUSIZ = %d\n",BUFSIZ);
}
