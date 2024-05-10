#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

void error_handling(char *message);

int main(int argc, char *argv[]) 
{
	int sock, state;

//nagle 알고리즘의 설정상태 확인하는 코드
	int opt_val;
    socklen_t opt_len;
   
    sock=socket(PF_INET, SOCK_STREAM,0);

    opt_len=sizeof(opt_val);
    state=getsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (void*)&opt_val, &opt_len);
    
    if(state)
    error_handling("getsockpt() error");
    if(opt_val)
    printf("BeforNagle: off\n");
    else
        printf("BeforeNagle: on\n");

//opt_val = 1 -> off, opt_val = 0 -> on
    opt_val=1;
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,(void*)&opt_val, sizeof(opt_val));
	
	if(state)
        error_handling("getsockpt() error");
    if(opt_val)
    printf("AfterNagle: off\n");
    else
        printf("AfterNagle: on\n");

    return 0;

}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}