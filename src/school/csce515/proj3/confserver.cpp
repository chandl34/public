#include <arpa/inet.h>	
#include <iostream>
#include <list>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


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


// Server socket functions
void Bind(int sockfd, struct sockaddr_in* addr){	
	if(bind(sockfd, (struct sockaddr*) addr, sizeof(*addr)) < 0)
		error("bind() error\n");
}

int getPort(int sockfd){
	struct sockaddr_in serv;
	socklen_t len = sizeof(serv);
	if(getsockname(sockfd, (struct sockaddr*) &serv, &len) < 0)
		return -1;
	return ntohs(serv.sin_port);
}


// I/O
int Recvfrom(int sockfd, char* buffer, int size, 
			 struct sockaddr_in* addr){
	socklen_t len = sizeof(*addr);	
	int n = recvfrom(sockfd, buffer, size, 0, 
					 (struct sockaddr*) addr, &len);
	if(n < 0)
		error("recvfrom() error\n");
	return n;
}

int Sendto(int sockfd, char* buffer, int size, 
		   struct sockaddr_in* addr){
	socklen_t len = sizeof(*addr);	
	int n = sendto(sockfd, buffer, size, 0, 
				   (struct sockaddr*) addr, len);
	if(n < 0)
		error("sendto() error\n");
	return n;
}


int main (int argc, char* const argv[]) {
	int sockfd;
	struct sockaddr_in servaddr, recvaddr;
	int n;
	char buffer[MAXLINE];
	char ipport[50];
	list<sockaddr_in> client;
	list<sockaddr_in>::iterator iter;
	
	
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = 0;
		
	Bind(sockfd, &servaddr);
	
	printf("Server listening on port %i\n",
		   getPort(sockfd));
	
	
	while(true){				
		bzero((char*) &buffer, sizeof(buffer));	
		
		// Receive client JOIN or LEAVE message
		n = Recvfrom(sockfd, buffer, MAXLINE, &recvaddr);
				
		printf("%i:%i>  ", recvaddr.sin_addr.s_addr, 
						   ntohs(recvaddr.sin_port));
		fwrite(buffer, sizeof(char), n, stdout);
		cout << endl;
		
		// Append IP and port #
		sprintf(ipport, " %i %i", recvaddr.sin_addr.s_addr, recvaddr.sin_port);	
		strcat(buffer, ipport);
				
		// Send new client info to all other clients		
		for(iter = client.begin(); iter != client.end(); iter++)
			Sendto(sockfd, buffer, n + sizeof(ipport), &(*iter));
		
		// Check message type
		if(strncmp(buffer, "JOIN", 4) == 0){
			// Send all listed clients to new client			
			for(iter = client.begin(); iter != client.end(); iter++){
				bzero((char*) &buffer, sizeof(buffer));	
				sprintf(ipport, "JOIN %i %i", (*iter).sin_addr.s_addr, (*iter).sin_port);
				strcat(buffer, ipport);
				Sendto(sockfd, buffer, n + sizeof(ipport), &recvaddr);
			}			
			
			client.push_back(recvaddr);			
		}
		else if(strncmp(buffer, "LEAVE", 5) == 0){	
			for(iter = client.begin(); iter != client.end(); iter++){
				if((*iter).sin_addr.s_addr == recvaddr.sin_addr.s_addr &&
				   (*iter).sin_port == recvaddr.sin_port){
					client.erase(iter);
					break;
				}
			}
		}	
		
		//printf("clients: %i\n", client.size());				
	}
	
    return 0;
}
