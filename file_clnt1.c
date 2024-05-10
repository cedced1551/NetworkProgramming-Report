#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	//int sd;
	FILE *fp;
	char mesage[BUF_SIZE];
	char cfile_name[BUF_SIZE];
	char sfile_name[BUF_SIZE];
	int read_cnt;
	struct sockaddr_in serv_adr;
	if(argc!=3) {
		printf("Usage: %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	

	sock=socket(PF_INET, SOCK_STREAM, 0); 
	if(sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("connect()");

		fputs("Input file: ", stdout);
		scanf("%s", sfile_name);
		fputs("Output file: ", stdout);
		scanf("%s", cfile_name);

	//printf("Input file name: ");
	//scanf("%s", file_name);
	//fp=fopen(file_name, "wb");
	

	//connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
	//write(sock, file_name, strlen(file_name)+1);	

	while((read_cnt=read(sock, message, BUF_SIZE))!=0)
	{
		if(read_cnt==-1)
		error_handling("read() error");

		if(message[0]==0)
		printf("파일을 찾을 수 없음.\n");
		break;
	}
	else{
		fp=fopen(cfile_name, "wb");
		fwrite((void*)message,1,read_cnt,fp);
		fputs("received file data", stdout);
		write(sock, "ThankYou", 10);
		fclose(fp);
	}
		fwrite((void*)buf, 1, read_cnt, fp);
	
	//fclose(fp);
	close(sock);
	return 0;
}
 
//void error_handling(char *message)
 //{
	//fputs(message, stderr);
	//fputc('\n', stderr);
	//exit(1);
//}
