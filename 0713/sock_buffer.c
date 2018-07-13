#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>

void error_handling(char *message)
{
        fputs(message, stderr);
        fputc('\n', stderr);
        exit(1);
}

int main(int argc, char *argv[])
{
	int tcp_sock;
	int snd_buf, rcv_buf;
	socklen_t optlen;
	int state;

	optlen = sizeof(snd_buf);

	// TCP socket생성
	tcp_sock = socket(PF_INET,SOCK_STREAM,0);

	// TCP read : snd_buf
	state = getsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &optlen);
	if(state)
	{	
		error_handling("getsockopt() rnd_buf error");
	}
	printf("Socket output buffer size : %d\n", snd_buf);
	
	// TCP read : rcv_buf
	
	optlen = sizeof(rcv_buf);

        state = getsockopt(tcp_sock, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, &optlen);
        if(state)
        {
                error_handling("getsockopt() rcv_buf error");
        }
        printf("Socket input buffer size : %d\n", rcv_buf);

        

	return 0;
}
 

