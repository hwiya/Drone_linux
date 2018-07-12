#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include"operate.h"

#define BUFSIZE 50

void error_handling(char *message);

int main(int argc, char **argv)
{
	int sock, i, p;
	struct cal Cal;
	struct sockaddr_in serv_addr;
	char message[BUFSIZE];
	int str_len;
	int temp;

	printf("Operand Count : ");
	scanf("%d", &temp);
	Cal.operandCount=(char)temp;
	
	for(i=0;i<Cal.operandCount;i++)
	{
		printf("Operand%d : ",i+1);
		scanf("%d", &Cal.operand[i]);
	}

	printf("operation : ");
	scanf("%c", &Cal.operation);
	scanf("%c", &Cal.operation);
	
	if(argc != 3)
	{
		printf("Usage : %s [IP] [PORT]\n", argv[0]);
		exit(1);
	}

	//1.socket()
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		error_handling("socket() error");
	}

	//2.서버의 주소(ip, port)값을 설정
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	//3. connect()
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
	{
		error_handling("connect() error");
	}
	
	//4. Data Transfer
	str_len = read(sock, message, sizeof(message) - 1);
	if(str_len == -1)
	{
		error_handling("read() error");
	}
	
	printf("Message from server : %s\n", message);
	write(sock, &Cal, sizeof(struct cal));
	// 5. close()
	close(sock);
	
	return 0;
}

void error_handling(char *message)
{
        fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
