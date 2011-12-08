#include <netdb.h> 
#include <netinet/in.h>		
#include <arpa/inet.h>		
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>


using namespace std;


const int MAXLINE = 4096;


void error(const char* msg){
    perror(msg);
    exit(0);
}


// General socket functions
int Socket(int family, int type, int protocol){
	int n = socket(family, type, protocol);
	if(n < 0)
		error("socket() error\n");
	return n;
}

void Close(int sockfd){
	if(close(sockfd) < 0)
		error("close() error\n");
}


// Client socket functions
void Connect(int sockfd, struct sockaddr_in* addr){	
	socklen_t len = sizeof(*addr);	
	if(connect(sockfd, (struct sockaddr*) addr, len) < 0)
		error("connect() error\n");
}


// I/0
int Read(int sockfd, char* buffer, int s){
	int n = read(sockfd, buffer, s);
	if(n < 0)
		error("read() error\n");
	return n;
}

int Write(int sockfd, char* buffer, int s){
	int n = write(sockfd, buffer, s);
	if(n < 0)
		error("write() error\n");
	return n;
}


int main (int argc, char * const argv[]) {
	char buffer[MAXLINE];
	int sockfd;
    struct sockaddr_in servAddr;
    struct hostent* server;
	int n;
	
	if(argc < 3)
		error("usage %s hostname port");
	
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	server = gethostbyname(argv[1]);
	
	bzero((char*) &servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
    bcopy((char*) server->h_addr,
		  (char*) &servAddr.sin_addr.s_addr,
		  server->h_length);
    servAddr.sin_port = htons(atoi(argv[2]));
	
	Connect(sockfd, &servAddr);
	
	printf("Connected...\n");
	
	if(fork() == 0){
		while(true){
			if(fgets(buffer, MAXLINE-1, stdin) == NULL)		// Catches CTRL + D
				exit(0);
			Write(sockfd, buffer, strlen(buffer));	
		}		
	}
	
	while(true){
		if((n = Read(sockfd, buffer, MAXLINE)) == 0)
			error("server terminated connection");
		printf("> ");	
		fwrite(buffer, sizeof(char), n, stdout);
	}	
	
    return 0;
}
