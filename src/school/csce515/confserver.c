#include <netinet/in.h>		// IPv4 socket address struct
#include <arpa/inet.h>		// address conversion
#include <sys/select.h>
#include <sys/time.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


const int MAXLINE = 4096, LISTENQ = 1024;


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


// Server socket functions
void Bind(int sockfd, struct sockaddr_in* addr){	
	if(bind(sockfd, (struct sockaddr*) addr, sizeof(*addr)) < 0)
		error("bind() error\n");
}

void Listen(int sockfd){
	if(listen(sockfd, LISTENQ) < 0)
		error("listen() error\n");
}

int Accept(int sockfd){	
	int n = accept(sockfd, 0, 0);
	if(n < 0)
		error("accept() error\n");
	return n;
}

int Select(int maxfdp1, fd_set* readset, fd_set* writeset, 
		   fd_set* exceptset, struct timeval* timeout){
	int n = select(maxfdp1, readset, writeset, exceptset, timeout);
	if(n < 0)
		error("select() error\n");	
	return n;
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


int getPort(int sockfd){
	struct sockaddr_in serv;
	socklen_t len = sizeof(serv);
	if(getsockname(sockfd, (struct sockaddr*) &serv, &len) < 0)
		return -1;
	return ntohs(serv.sin_port);
}


int main (int argc, char* const argv[]) {
	int maxi, maxfd, i, j;
	ssize_t n;
	fd_set rset, allset;
	int nready, client[FD_SETSIZE];
	char buffer[MAXLINE];
	int listenfd, connfd, sockfd;
	struct sockaddr_in serverAddr;
		
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = 0;
	
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);	
	Bind(listenfd, &serverAddr);	
	Listen(listenfd);
	
	printf("Server ready and listening for new connections on port %i\n",
		   getPort(listenfd));
	
	maxfd = listenfd;
	maxi = -1;
	for(i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
	
	while(true){
		rset = allset;
		nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);
		
		if(FD_ISSET(listenfd, &rset)){
			connfd = Accept(listenfd);	
			printf("Client connected...\n");
			
			for(i = 0; i < FD_SETSIZE; i++){
				if(client[i] < 0){
					client[i] = connfd;
					break;					
				}				
			}
			if(i == FD_SETSIZE)
				error("too many clients");
			
			FD_SET(connfd, &allset);
			if(connfd > maxfd)
				maxfd = connfd;
			if(i > maxi)
				maxi = i;
			if(--nready <= 0)
				continue;
		}
		for(i = 0; i <= maxi; i++){
			if((sockfd = client[i]) < 0)
				continue;
			if(FD_ISSET(sockfd, &rset)){
				if((n = Read(sockfd, buffer, MAXLINE)) == 0){
					Close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
					printf("Client disconnected...\n");
				}
				else{
					printf("> ");	
					fwrite(buffer, sizeof(char), n, stdout);
					for(j = 0; j <= maxi; j++){
						if((sockfd = client[j]) < 0)
							continue;
						Write(sockfd, buffer, n);						
					}
				}
				if(--nready <= 0)
					break;				
			}			
		}
	}
	
    return 0;
}
