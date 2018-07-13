#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include"operate.h"

void error_handling(char *message);

int main(int argc, char **argv)
{
	int serv_sock;
	int clnt_sock;
	int p;
	int str_len;
	int result;
	int i;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	struct cal Cal;

	socklen_t clnt_addr_size;
	
	char message[] = "Hello World!";
	char *ipaddr;

	
	if(argc != 2)
	{
		printf("Usage : %s [port]\n", argv[0]);
		exit(1);
	}
	
	//1. socket() 소켓을 생성한다.
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	if(serv_sock == -1)
	{
		error_handling("socket() error");
	}
	//2. 서버의 주소값(ip, port)을 설정한다.
	memset(&serv_addr, 0 , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	//IP설정
	serv_addr.sin_port = htons(atoi(argv[1]));	//PORT설정

	//3. 서버의 주소값을 bind한다.
	if(bind(serv_sock, (struct sockaddr*) & serv_addr, sizeof(serv_addr)) == -1)
	{
		error_handling("bing() error");
	}
	
	//4. liste() 동시접속 최대허용수를 5로 설정한다.
	if(listen(serv_sock, 5) == -1)
	{
		error_handling("listen() error");
	}
	clnt_addr_size = sizeof(clnt_addr);
	
	//5. accept()
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	
	if(clnt_sock == -1)
	{
		error_handling("accept() error");
	}
	write(clnt_sock, message, sizeof(message));
	str_len = read(clnt_sock, &Cal, sizeof(struct cal) - 1);
	ipaddr = inet_ntoa(clnt_addr.sin_addr);
	printf("client ip addr : %s\n", ipaddr);
	
        p = (int)Cal.operation;

	if(p == '+')
	{
		result = Cal.operand[0];
		for(i=1;i<Cal.operandCount;i++)
		{
			result = result + Cal.operand[i];
		}
		printf("operand result(+) : %d\n", result);
	}
	else if(p == '-')
	{
		result = Cal.operand[0];
		for(i=1;i<Cal.operandCount;i++)
		{
			result = result - Cal.operand[i];
		}
		printf("operand result(-) : %d\n", result);
	}
	else if(p == '*')
	{
		result = Cal.operand[0];
		for(i=1;i<Cal.operandCount;i++)
		{
			result = result * Cal.operand[i];
		}
		printf("operand result(*) : %d\n", result);
	}
	else
	{
		printf("operation error\n");
	}

	close(clnt_sock);
	close(serv_sock);
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
